#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <winsock2.h>
#include <ws2tcpip.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cwchar>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "Packet.h"

#pragma comment(lib, "ws2_32.lib")

namespace
{
    using Clock = std::chrono::steady_clock;

    struct Config
    {
        std::wstring host = L"127.0.0.1";
        uint16_t port = 9000;
        int clients = 16;
        int durationSec = 60;
        int holdMs = 1000;
        int moveHz = 10;
        int recvTimeoutMs = 3000;
        int startDelayMs = 10;
        int userStart = 1;
        std::wstring userPrefix = L"load";
        std::wstring password = L"pass1234";
        std::wstring scenario = L"room"; // connect, register, login, room, move
    };

    struct Stats
    {
        std::atomic<uint64_t> attempts = 0;
        std::atomic<uint64_t> connectOk = 0;
        std::atomic<uint64_t> connectFail = 0;
        std::atomic<uint64_t> accessAllow = 0;
        std::atomic<uint64_t> registerOk = 0;
        std::atomic<uint64_t> registerDeny = 0;
        std::atomic<uint64_t> loginOk = 0;
        std::atomic<uint64_t> loginDeny = 0;
        std::atomic<uint64_t> roomEnter = 0;
        std::atomic<uint64_t> sendFail = 0;
        std::atomic<uint64_t> recvFail = 0;
        std::atomic<uint64_t> disconnects = 0;
        std::atomic<uint64_t> movePackets = 0;
        std::atomic<uint64_t> iterations = 0;
    };

    struct RecvPacket
    {
        PacketHeader header{};
        std::vector<char> body;
    };

    std::mutex g_LogLock;

    void PrintUsage()
    {
        std::wcout
            << L"StressClient options:\n"
            << L"  --host 127.0.0.1\n"
            << L"  --port 9000\n"
            << L"  --clients 16\n"
            << L"  --duration 60\n"
            << L"  --scenario connect|register|login|room|move\n"
            << L"  --user-prefix load\n"
            << L"  --user-start 1\n"
            << L"  --password pass1234\n"
            << L"  --hold-ms 1000\n"
            << L"  --move-hz 10\n";
    }

    bool ParseInt(const wchar_t* text, int& out)
    {
        wchar_t* end = nullptr;
        long value = wcstol(text, &end, 10);
        if (!end || *end != L'\0') { return false; }
        out = static_cast<int>(value);
        return true;
    }

    Config ParseArgs(int argc, wchar_t** argv)
    {
        Config cfg;
        for (int i = 1; i < argc; ++i)
        {
            std::wstring arg = argv[i];
            auto requireValue = [&](const wchar_t* name) -> wchar_t* {
                if (i + 1 >= argc)
                {
                    std::wcerr << L"Missing value for " << name << L"\n";
                    return nullptr;
                }
                return argv[++i];
            };

            if (arg == L"--help" || arg == L"-h")
            {
                PrintUsage();
                std::exit(0);
            }
            else if (arg == L"--host")
            {
                if (auto* v = requireValue(L"--host")) { cfg.host = v; }
            }
            else if (arg == L"--port")
            {
                int v = 0;
                if (auto* text = requireValue(L"--port"); text && ParseInt(text, v)) { cfg.port = static_cast<uint16_t>(v); }
            }
            else if (arg == L"--clients")
            {
                int v = 0;
                if (auto* text = requireValue(L"--clients"); text && ParseInt(text, v)) { cfg.clients = v; }
            }
            else if (arg == L"--duration")
            {
                int v = 0;
                if (auto* text = requireValue(L"--duration"); text && ParseInt(text, v)) { cfg.durationSec = v; }
            }
            else if (arg == L"--scenario")
            {
                if (auto* v = requireValue(L"--scenario")) { cfg.scenario = v; }
            }
            else if (arg == L"--user-prefix")
            {
                if (auto* v = requireValue(L"--user-prefix")) { cfg.userPrefix = v; }
            }
            else if (arg == L"--user-start")
            {
                int v = 0;
                if (auto* text = requireValue(L"--user-start"); text && ParseInt(text, v)) { cfg.userStart = v; }
            }
            else if (arg == L"--password")
            {
                if (auto* v = requireValue(L"--password")) { cfg.password = v; }
            }
            else if (arg == L"--hold-ms")
            {
                int v = 0;
                if (auto* text = requireValue(L"--hold-ms"); text && ParseInt(text, v)) { cfg.holdMs = v; }
            }
            else if (arg == L"--move-hz")
            {
                int v = 0;
                if (auto* text = requireValue(L"--move-hz"); text && ParseInt(text, v)) { cfg.moveHz = v; }
            }
            else if (arg == L"--recv-timeout-ms")
            {
                int v = 0;
                if (auto* text = requireValue(L"--recv-timeout-ms"); text && ParseInt(text, v)) { cfg.recvTimeoutMs = v; }
            }
            else if (arg == L"--start-delay-ms")
            {
                int v = 0;
                if (auto* text = requireValue(L"--start-delay-ms"); text && ParseInt(text, v)) { cfg.startDelayMs = v; }
            }
        }

        if (cfg.clients < 1) { cfg.clients = 1; }
        if (cfg.durationSec < 1) { cfg.durationSec = 1; }
        if (cfg.moveHz < 1) { cfg.moveHz = 1; }
        return cfg;
    }

    std::wstring MakeUserName(const Config& cfg, int clientIndex)
    {
        std::wstringstream ss;
        ss << cfg.userPrefix << std::setw(4) << std::setfill(L'0') << (cfg.userStart + clientIndex);
        return ss.str();
    }

    bool SendAll(SOCKET sock, const char* data, int size)
    {
        int sentTotal = 0;
        while (sentTotal < size)
        {
            int sent = send(sock, data + sentTotal, size - sentTotal, 0);
            if (sent <= 0) { return false; }
            sentTotal += sent;
        }
        return true;
    }

    bool SendPacketToServer(SOCKET sock, uint16_t packetID, const std::vector<char>& body)
    {
        std::vector<char> packet = MakePacket(packetID, body);
        return SendAll(sock, packet.data(), static_cast<int>(packet.size()));
    }

    bool RecvAll(SOCKET sock, char* data, int size)
    {
        int receivedTotal = 0;
        while (receivedTotal < size)
        {
            int received = recv(sock, data + receivedTotal, size - receivedTotal, 0);
            if (received <= 0) { return false; }
            receivedTotal += received;
        }
        return true;
    }

    bool RecvOnePacket(SOCKET sock, RecvPacket& out)
    {
        PacketHeader header{};
        if (!RecvAll(sock, reinterpret_cast<char*>(&header), sizeof(header)))
        {
            return false;
        }

        if (header.packet_size < sizeof(PacketHeader) || header.packet_size > 65535)
        {
            return false;
        }

        out.header = header;
        out.body.clear();

        int bodySize = static_cast<int>(header.packet_size - sizeof(PacketHeader));
        if (bodySize > 0)
        {
            out.body.resize(bodySize);
            if (!RecvAll(sock, out.body.data(), bodySize))
            {
                return false;
            }
        }

        return true;
    }

    bool WaitForAnyPacket(SOCKET sock, const std::vector<uint16_t>& ids, int timeoutMs, RecvPacket* matched)
    {
        auto deadline = Clock::now() + std::chrono::milliseconds(timeoutMs);
        while (Clock::now() < deadline)
        {
            fd_set readSet;
            FD_ZERO(&readSet);
            FD_SET(sock, &readSet);

            timeval tv{};
            tv.tv_sec = 0;
            tv.tv_usec = 100 * 1000;

            int ret = select(0, &readSet, nullptr, nullptr, &tv);
            if (ret == SOCKET_ERROR || ret == 0)
            {
                continue;
            }

            RecvPacket packet{};
            if (!RecvOnePacket(sock, packet))
            {
                return false;
            }

            for (uint16_t id : ids)
            {
                if (packet.header.packet_ID == id)
                {
                    if (matched) { *matched = std::move(packet); }
                    return true;
                }
            }
        }

        return false;
    }

    void DrainAvailable(SOCKET sock)
    {
        while (true)
        {
            fd_set readSet;
            FD_ZERO(&readSet);
            FD_SET(sock, &readSet);

            timeval tv{};
            tv.tv_sec = 0;
            tv.tv_usec = 0;

            int ret = select(0, &readSet, nullptr, nullptr, &tv);
            if (ret <= 0) { return; }

            RecvPacket ignored{};
            if (!RecvOnePacket(sock, ignored)) { return; }
        }
    }

    SOCKET ConnectSocket(const Config& cfg)
    {
        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET) { return INVALID_SOCKET; }

        int timeout = cfg.recvTimeoutMs;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(cfg.port);

        if (InetPtonW(AF_INET, cfg.host.c_str(), &addr.sin_addr) != 1)
        {
            closesocket(sock);
            return INVALID_SOCKET;
        }

        if (connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR)
        {
            closesocket(sock);
            return INVALID_SOCKET;
        }

        return sock;
    }

    bool RegisterAccount(SOCKET sock, const Config& cfg, const std::wstring& user, Stats& stats)
    {
        if (!SendPacketToServer(sock, PKT_C2S_REGISTER_REQ, MakeLoginBody(user, cfg.password)))
        {
            stats.sendFail++;
            return false;
        }

        RecvPacket response{};
        if (!WaitForAnyPacket(sock, { PKT_S2C_REGISTER_OK, PKT_S2C_REGISTER_DENY }, cfg.recvTimeoutMs, &response))
        {
            stats.recvFail++;
            return false;
        }

        if (response.header.packet_ID == PKT_S2C_REGISTER_OK)
        {
            stats.registerOk++;
            return true;
        }

        stats.registerDeny++;
        return false;
    }

    bool Login(SOCKET sock, const Config& cfg, const std::wstring& user, Stats& stats)
    {
        if (!SendPacketToServer(sock, PKT_C2S_LOGIN_REQ, MakeLoginBody(user, cfg.password)))
        {
            stats.sendFail++;
            return false;
        }

        RecvPacket response{};
        if (!WaitForAnyPacket(sock, { PKT_S2C_LOGIN_OK, PKT_S2C_LOGIN_DENY }, cfg.recvTimeoutMs, &response))
        {
            stats.recvFail++;
            return false;
        }

        if (response.header.packet_ID == PKT_S2C_LOGIN_OK)
        {
            stats.loginOk++;
            return true;
        }

        stats.loginDeny++;
        return false;
    }

    bool CreateRoom(SOCKET sock, const Config& cfg, Stats& stats)
    {
        if (!SendPacketToServer(sock, PKT_C2S_ROOM_CREATE_REQ, {}))
        {
            stats.sendFail++;
            return false;
        }

        RecvPacket response{};
        if (!WaitForAnyPacket(sock, { PKT_S2C_ROOM_ENTER, PKT_S2C_ERROR }, cfg.recvTimeoutMs, &response))
        {
            stats.recvFail++;
            return false;
        }

        if (response.header.packet_ID == PKT_S2C_ROOM_ENTER)
        {
            stats.roomEnter++;
            return true;
        }

        return false;
    }

    bool RunSession(const Config& cfg, int clientIndex, Stats& stats, Clock::time_point endTime)
    {
        stats.attempts++;

        SOCKET sock = ConnectSocket(cfg);
        if (sock == INVALID_SOCKET)
        {
            stats.connectFail++;
            return false;
        }

        stats.connectOk++;

        RecvPacket response{};
        if (WaitForAnyPacket(sock, { PKT_S2C_ACCESS_ALLOW }, cfg.recvTimeoutMs, &response))
        {
            stats.accessAllow++;
        }

        if (cfg.scenario == L"connect")
        {
            closesocket(sock);
            stats.disconnects++;
            return true;
        }

        const std::wstring user = MakeUserName(cfg, clientIndex);

        if (cfg.scenario == L"register")
        {
            RegisterAccount(sock, cfg, user, stats);
            closesocket(sock);
            stats.disconnects++;
            return true;
        }

        if (!Login(sock, cfg, user, stats))
        {
            closesocket(sock);
            stats.disconnects++;
            return false;
        }

        if (cfg.scenario == L"login")
        {
            closesocket(sock);
            stats.disconnects++;
            return true;
        }

        if (!CreateRoom(sock, cfg, stats))
        {
            closesocket(sock);
            stats.disconnects++;
            return false;
        }

        SendPacketToServer(sock, PKT_C2S_READY_REQ, {});

        if (cfg.scenario == L"move")
        {
            SendPacketToServer(sock, PKT_C2S_GAME_START_REQ, {});

            const auto frameDelay = std::chrono::milliseconds(1000 / cfg.moveHz);
            auto localEnd = (std::min)(endTime, Clock::now() + std::chrono::milliseconds(cfg.holdMs));
            int frame = 0;

            while (Clock::now() < localEnd)
            {
                float x = static_cast<float>((frame % 100) * 10);
                float y = static_cast<float>(clientIndex * 20);
                float yaw = static_cast<float>((frame * 5) % 360);
                if (!SendPacketToServer(sock, PKT_C2S_MOVE_KEYINPUT, MakeMoveBody(x, y, 0.0f, yaw, yaw, 0.3f, 0.6f)))
                {
                    stats.sendFail++;
                    break;
                }

                stats.movePackets++;
                DrainAvailable(sock);
                std::this_thread::sleep_for(frameDelay);
                ++frame;
            }
        }
        else
        {
            auto localEnd = (std::min)(endTime, Clock::now() + std::chrono::milliseconds(cfg.holdMs));
            while (Clock::now() < localEnd)
            {
                DrainAvailable(sock);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }

        SendPacketToServer(sock, PKT_C2S_ROOM_LEAVE_REQ, {});
        closesocket(sock);
        stats.disconnects++;
        return true;
    }

    void Worker(const Config& cfg, int clientIndex, Stats& stats, Clock::time_point endTime)
    {
        while (Clock::now() < endTime)
        {
            RunSession(cfg, clientIndex, stats, endTime);
            stats.iterations++;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void PrintStats(const Stats& stats, int elapsedSec)
    {
        std::lock_guard<std::mutex> lock(g_LogLock);
        std::wcout
            << L"[elapsed " << elapsedSec << L"s]"
            << L" attempts=" << stats.attempts.load()
            << L" connectOk=" << stats.connectOk.load()
            << L" connectFail=" << stats.connectFail.load()
            << L" access=" << stats.accessAllow.load()
            << L" regOk=" << stats.registerOk.load()
            << L" regDeny=" << stats.registerDeny.load()
            << L" loginOk=" << stats.loginOk.load()
            << L" loginDeny=" << stats.loginDeny.load()
            << L" roomEnter=" << stats.roomEnter.load()
            << L" move=" << stats.movePackets.load()
            << L" sendFail=" << stats.sendFail.load()
            << L" recvFail=" << stats.recvFail.load()
            << L" disconnects=" << stats.disconnects.load()
            << L"\n";
    }
}

int wmain(int argc, wchar_t** argv)
{
    Config cfg = ParseArgs(argc, argv);

    WSADATA wsa{};
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::wcerr << L"WSAStartup failed\n";
        return 1;
    }

    Stats stats;
    auto start = Clock::now();
    auto endTime = start + std::chrono::seconds(cfg.durationSec);

    {
        std::lock_guard<std::mutex> lock(g_LogLock);
        std::wcout
            << L"StressClient target=" << cfg.host << L":" << cfg.port
            << L" clients=" << cfg.clients
            << L" duration=" << cfg.durationSec << L"s"
            << L" scenario=" << cfg.scenario
            << L" userPrefix=" << cfg.userPrefix
            << L" userStart=" << cfg.userStart
            << L"\n";

        if (cfg.scenario == L"move")
        {
            std::wcout << L"Note: move packets require the server session state to allow PKT_C2S_MOVE_KEYINPUT after game start.\n";
        }
    }

    std::vector<std::thread> threads;
    threads.reserve(cfg.clients);

    for (int i = 0; i < cfg.clients; ++i)
    {
        threads.emplace_back(Worker, std::cref(cfg), i, std::ref(stats), endTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.startDelayMs));
    }

    while (Clock::now() < endTime)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        int elapsed = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - start).count());
        PrintStats(stats, elapsed);
    }

    for (std::thread& t : threads)
    {
        if (t.joinable()) { t.join(); }
    }

    int elapsed = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - start).count());
    PrintStats(stats, elapsed);

    WSACleanup();
    return 0;
}
