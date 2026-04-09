#pragma once

#include "logging.hpp"


// logger Macro
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

#define LOG_INFO(...) LogWrapper("INFO", __VA_ARGS__)
#define LOG_ERROR(...) LogWrapper("ERROR", __VA_ARGS__)
#define LOG_WARN(...) LogWrapper("WARN", __VA_ARGS__)