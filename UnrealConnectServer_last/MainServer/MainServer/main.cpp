#include <thread>
#include <vector>

// Must include first winsock and ws2tcpip than Windows.h
#include "server.h"

#include <Windows.h>


const UINT16 MAX_CLIENT_NUM = 10;
const UINT32 MAX_IO_WORKER_THREADS = 4;


int main()
{
	IOCPServer server;

	server.InitLogger();

	if (server.Init(9000, 8)) {
		LOG_INFO("Server Initalized Successfully!");
		server.Start();
	}

	else { LOG_ERROR("Failed to Server Initalization!"); return -1; }

	// Wait for MainThread not to end
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	LOG_INFO("Server Closed!");
	return 0;
}