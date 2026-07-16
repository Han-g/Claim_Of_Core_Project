#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

// Include winsock headers before Windows.h.
#include "server.h"

#include <Windows.h>


const UINT16 MAX_CLIENT_NUM = 10;
const UINT32 MAX_IO_WORKER_THREADS = 4;

namespace
{
	std::atomic_bool g_StopRequested = false;

	BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType)
	{
		switch (ctrlType)
		{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			g_StopRequested.store(true);
			return TRUE;

		default:
			return FALSE;
		}
	}
}

int main()
{
	SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

	IOCPServer server;

	server.InitLogger();

	if (server.Init(9000, 3000)) {
		LOG_INFO("Server Initalized Successfully!");
		server.Start();
	}

	else { LOG_ERROR("Failed to Server Initalization!"); return -1; }

	// Keep the main thread alive and drive the server frame loop.
	while (!g_StopRequested.load()) {
		static auto lastTime = std::chrono::steady_clock::now();
		auto now = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration<float>(now - lastTime).count();
		lastTime = now;

		server.GameFrameProtocol(deltaTime);

		// Run the frame loop at roughly 60 frames per second.
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
	server.Stop();

	SetConsoleCtrlHandler(ConsoleCtrlHandler, FALSE);
	LOG_INFO("Server Closed!");

	return 0;
}