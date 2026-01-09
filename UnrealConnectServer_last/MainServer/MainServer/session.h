#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

#include <queue>
#include <mutex>

#include <windows.h>

// Ring Buffer
#define BUF_SIZE 10240

typedef struct {
	unsigned int head;
	unsigned int tail;
	char data[BUF_SIZE];
} s_ringbuf;

inline int GetRingBufSize(s_ringbuf* buf) {
	if (buf->head >= buf->tail) { return (buf->head - buf->tail); }

	return (BUF_SIZE - buf->tail) + buf->head;
}

inline bool IsRingbufAvailalbe(s_ringbuf* buf) { return buf->head == buf->tail; }

// EnQueue 1 letter
inline void RingBufEnQueue(s_ringbuf* buf, char c) {
	unsigned int i = (unsigned int)(buf->head + 1) % BUF_SIZE;

	// Check Buffer is full
	if (i != buf->tail) {
		buf->data[buf->head] = c;
		buf->head = i;
	}
	else { LOG_ERROR("Buffer is no room to store data!"); }
}

// DeQueue 1 letter
inline char RingBufDeQueue(s_ringbuf* buf) {
	char c = '\0';

	// Check Buffer is empty
	if (buf->head == buf->tail) { LOG_ERROR("Buffer is empty!"); }

	else {
		c = buf->data[buf->tail];
		buf->tail = (unsigned int)(buf->tail + 1) % BUF_SIZE;
	}

	return c;
}

// Data Recived from WSARecv Copy to Ringbuffer
inline bool RingBufPush(s_ringbuf* buf, char* recvData, int len) {
	// Check Buffer overflow
	int freeSpace = BUF_SIZE - GetRingBufSize(buf) - 1;
	if (freeSpace < len) { LOG_ERROR("Buffer has no enough space"); return false; }

	int leftCapacity = BUF_SIZE - buf->head;

	// Can Copy At first
	if (leftCapacity >= len) {
		memcpy(&buf->data[buf->head], recvData, len);
		buf->head = (buf->head + len) % BUF_SIZE;
	}

	// Need Wrap around over the end of Buffer
	else {
		memcpy(&buf->data[buf->head], recvData, leftCapacity);
		memcpy(&buf->data[0], recvData + leftCapacity, len - leftCapacity);
		buf->head = (len - leftCapacity);
	}

	return true;
}

// Data Read for cheak header
inline bool RingBufPeek(s_ringbuf* buf, char* dest, int len) {
	if (GetRingBufSize(buf) < len) {
		LOG_ERROR("Read size is less than Data size");
		return false;
	}

	int freeSpace = BUF_SIZE - buf->tail;

	if (freeSpace >= len) { memcpy(dest, &buf->data[buf->tail], len); }
	else {
		memcpy(dest, &buf->data[buf->tail], freeSpace);
		memcpy(dest + freeSpace, &buf->data[0], len - freeSpace);
	}

	return true;
}

// Data delete
inline void RingBufpop(s_ringbuf* buf, int len) {
	buf->tail = (buf->tail + len) % BUF_SIZE;
}


// Check kind of IO Work
enum class IO_OPERATION {
	RECV,
	SEND,
	AWAIT
};

// Extend WSAOVERLAPPED by containing IO work type
struct OverlappedEx : public WSAOVERLAPPED {
	IO_OPERATION type;
};


struct GameData {
	bool isConnected = false;
	float x, y, z;

};

// Client Session Info (need to contain at "session.h")
struct Session {
	SOCKET socket;
	int sessionID;

	GameData gameDatas;

	char TempBuffer[1024];
	s_ringbuf recvBuffer;
	OverlappedEx recvOverlapped;

	bool isSending = false;
	std::queue<std::vector<char>> sendQueue;
	std::mutex sendLock;
	OverlappedEx sendOverlapped;

	Session() {
		socket = INVALID_SOCKET;
		sessionID = -1;

		ZeroMemory(TempBuffer, sizeof(TempBuffer));
		ZeroMemory(&recvBuffer, sizeof(s_ringbuf));
		ZeroMemory(&recvOverlapped, sizeof(OverlappedEx));
		recvOverlapped.type = IO_OPERATION::RECV;

		isSending = false;
		ZeroMemory(&sendOverlapped, sizeof(OverlappedEx));
		sendOverlapped.type = IO_OPERATION::SEND;
	}
};