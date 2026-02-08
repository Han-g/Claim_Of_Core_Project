// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

 // Sort by 1Byte For Communicate Protocol with Server
enum PacketID : uint16 {
	PKT_S2C_LOGIN_OK = 0,
	PKT_S2C_SNAPSHOT = 1,
	PKT_C2S_LOGIN = 10,
	PKT_C2S_MOVE = 11,
	PKT_C2S_ATTACK = 12,
};

struct  GameData {
	int userUID = 0;
	bool isConnected = false;

	int HP = 100;
	float x = 0, y = 0, z = 0;
	float rotate = 0;
	int animationNum = 0;
};

#pragma pack(push, 1)

struct FPacketHeader {
	uint16 PacketSize;
	uint16 PacketID;
};

struct FLoginPacket {
	FString userID;
	FString userPW;
};

struct FGamedataPacket {
	int sessionID;
	GameData data;
};

struct FMovePacket {
	float X, Y, Z;
	float Yaw;
	float VelocityX, VelocityY;
};

#pragma pack(pop)


class FSocket;

class CLAIM_OF_CORE_API ClientNetworking
{
public:
	ClientNetworking();
	~ClientNetworking();

	bool Connect(FString IP, int32 Port);
	void Disconnect();

	bool SendPacket(uint16 PacketID, const void* Data, uint16 PacketSize);
	void RecvPacketProcess();

	void LoginAccess(FString& ID, FString& PW);
	TArray<uint8> PacketAssemble(PacketID _ID, TArray<uint8> data);
	void PacketHandle(FPacketHeader* Header, uint8* LoadData);
	void PacketDeserialize(uint8* Data, uint16 DataSize);

private:
	FSocket* Socket;
	TArray<uint8> RecvBuffer;
public:
	bool IsLogin;
};
