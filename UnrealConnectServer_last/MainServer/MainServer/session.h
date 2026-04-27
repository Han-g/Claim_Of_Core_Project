#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

#include <queue>
#include <mutex>
#include <condition_variable>
#include "Packet.h"
#include "RoomManager.h"
#include "logger.h"

#include <windows.h>

// Ring buffer utilities
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

// Pushes a single byte into the ring buffer.
inline void RingBufEnQueue(s_ringbuf* buf, char c) {
	unsigned int i = (unsigned int)(buf->head + 1) % BUF_SIZE;

	// Ignore the write when the ring buffer is already full.
	if (i != buf->tail) {
		buf->data[buf->head] = c;
		buf->head = i;
	}
	else { LOG_ERROR("Buffer is no room to store data!"); }
}

// Pops a single byte from the ring buffer.
inline char RingBufDeQueue(s_ringbuf* buf) {
	char c = '\0';

	// Warn when attempting to read from an empty ring buffer.
	if (buf->head == buf->tail) { LOG_ERROR("Buffer is empty!"); }

	else {
		c = buf->data[buf->tail];
		buf->tail = (unsigned int)(buf->tail + 1) % BUF_SIZE;
	}

	return c;
}

// Copies bytes received by WSARecv into the ring buffer.
inline bool RingBufPush(s_ringbuf* buf, char* recvData, int len) {
	// Reject the write when the incoming payload would overflow the buffer.
	int freeSpace = BUF_SIZE - GetRingBufSize(buf) - 1;
	if (freeSpace < len) { LOG_ERROR("Buffer has no enough space"); return false; }

	int leftCapacity = BUF_SIZE - buf->head;

	// Copy directly when the remaining tail space is large enough.
	if (leftCapacity >= len) {
		memcpy(&buf->data[buf->head], recvData, len);
		buf->head = (buf->head + len) % BUF_SIZE;
	}

	// Wrap around when the payload crosses the end of the buffer.
	else {
		memcpy(&buf->data[buf->head], recvData, leftCapacity);
		memcpy(&buf->data[0], recvData + leftCapacity, len - leftCapacity);
		buf->head = (len - leftCapacity);
	}

	return true;
}

// Peeks at buffered data without consuming it.
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

// Removes consumed bytes from the ring buffer.
inline void RingBufpop(s_ringbuf* buf, int len) {
	buf->tail = (buf->tail + len) % BUF_SIZE;
}


// Identifies the type of asynchronous I/O work.
enum class IO_OPERATION {
	RECV,
	SEND,
	AWAIT
};

// Extends WSAOVERLAPPED with a lightweight I/O operation tag.
struct OverlappedEx : public WSAOVERLAPPED {
	IO_OPERATION type;
};

enum class ESessionState {
	LOGIN,
	LOBBY,
	ROOM,
	INGAME
};

struct MoveIntent
{
	float Forward = 0.0f; // W/S
	float Right = 0.0f;   // A/D
	float Yaw = 0.0f;     // Client View
	bool bHasInput = false;
};

// Stores the socket state and runtime data for one client session.
struct Session {
	SOCKET socket;
	int playerUID;
	int sessionID;
	int roomID;		// -1: Not Entering a Room
	int roomSlot;
	int teamID;

	bool isConnected = false;
	bool isReady = false;

	MoveIntent LastMoveIntent;
	std::mutex MoveIntentLock;

	ESessionState now_state;
	GameData gameDatas;
	std::wstring playerName;

	char TempBuffer[1024];
	s_ringbuf recvBuffer;
	OverlappedEx recvOverlapped;

	bool isSending = false;
	std::queue<std::vector<char>> sendQueue;
	std::mutex sendLock;
	OverlappedEx sendOverlapped;

	Session() {
		socket = INVALID_SOCKET;
		playerUID = -1;
		sessionID = -1;
		roomID = -1;
		roomSlot = -1;
		teamID = -1;

		now_state = ESessionState::LOGIN;

		ZeroMemory(TempBuffer, sizeof(TempBuffer));
		ZeroMemory(&recvBuffer, sizeof(s_ringbuf));
		ZeroMemory(&recvOverlapped, sizeof(OverlappedEx));
		recvOverlapped.type = IO_OPERATION::RECV;

		isSending = false;
		ZeroMemory(&sendOverlapped, sizeof(OverlappedEx));
		sendOverlapped.type = IO_OPERATION::SEND;
	}
};