#pragma once

#include "logging.hpp"

#include <filesystem>
#include <regex>

// Removes old ServerLog_*.log files that exceed the configured retention window.
inline void CleanupOldLogs(const std::string& prefix, int retentionDays) {
    namespace fs = std::filesystem;

    // Compute the cutoff timestamp in whole days.
    std::time_t now = std::time(nullptr);
    std::time_t cutoff = now - (retentionDays * 86400);

    // Expected log file name format: prefix_YYYY-MM-DD.log
    std::regex pattern(prefix + R"(_(\d{4})-(\d{2})-(\d{2})\.log)");

    try {
        for (const auto& entry : fs::directory_iterator(".")) {
            if (!entry.is_regular_file()) continue;

            std::string name = entry.path().filename().string();
            std::smatch match;
            if (!std::regex_match(name, match, pattern)) continue;

            // Convert the date encoded in the file name into a comparable timestamp.
            std::tm t{};
            t.tm_year = std::stoi(match[1]) - 1900;
            t.tm_mon = std::stoi(match[2]) - 1;
            t.tm_mday = std::stoi(match[3]);
            std::time_t fileDate = std::mktime(&t);

            if (fileDate < cutoff) {
                fs::remove(entry.path());
            }
        }
    }
    catch (...) {
        // Ignore directory access failures so logging setup does not abort startup.
    }
}

// Builds the timestamp prefix used by all server log lines.
inline std::string GetTimestamp()
{
	time_t now = time(nullptr);
	struct tm Time_struct;

	localtime_s(&Time_struct, &now);

	char buf[80];
	strftime(buf, sizeof(buf), "%Y-%m-%d | %H:%M:%S", &Time_struct);

	return std::string(buf);
}

template<typename ... Args>
void LogWrapper(const char* level, const char* format, Args ... args) {
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), format, args ...);

	char finalBuffer[1280];
	snprintf(finalBuffer, sizeof(finalBuffer), "[%s] [%s] %s\n", GetTimestamp().c_str(), level, buffer);

	logging::log(finalBuffer);
}

inline void LofWrapper(const char* level, const char* msg) {
	char buffer[1280];
	snprintf(buffer, sizeof(buffer), "[%s] [%s] %s\n", GetTimestamp().c_str(), level, msg);
	logging::log(buffer);
}

// Convenience wrappers for the shared logging backend.
#define LOG_INFO(...) LogWrapper("INFO", __VA_ARGS__)
#define LOG_ERROR(...) LogWrapper("ERROR", __VA_ARGS__)
#define LOG_WARN(...) LogWrapper("WARN", __VA_ARGS__)