#include <thread>
#include <vector>

// Include winsock headers before Windows.h.
#include "server.h"

#include <Windows.h>


const UINT16 MAX_CLIENT_NUM = 10;
const UINT32 MAX_IO_WORKER_THREADS = 4;


void Test(IOCPServer* server) {
	server->TestPacketProcessor();
}

int main()
{
	IOCPServer server;

	server.InitLogger();

	if (server.Init(9000, 3000)) {
		LOG_INFO("Server Initalized Successfully!");
		server.Start();
	}

	else { LOG_ERROR("Failed to Server Initalization!"); return -1; }

	//Test(&server);

	// Keep the main thread alive and drive the server frame loop.
	while (true) {
		static auto lastTime = std::chrono::steady_clock::now();
		auto now = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration<float>(now - lastTime).count();

		server.GameFrameProtocol(deltaTime);

		// Run the frame loop at roughly 60 frames per second.
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	LOG_INFO("Server Closed!");
	return 0;
}