#pragma once

#include <chrono>

class RoomManager
{
public:
	void MatchMaking();

private:
	int memberCounter;
	float gameTimer;
};

