// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientNetworking.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"


ClientNetworking::ClientNetworking()
{
	Socket = nullptr;
	IsLogin = false;
}

ClientNetworking::~ClientNetworking()
{
	Disconnect();
}

bool ClientNetworking::Connect(FString IP, int32 Port)
{
	// Disconnect If existing Connection exist
	Disconnect();

	// Create Socket
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
	if (!Socket) return false;

	// IP Address Parsing
	FIPv4Address IPAddress;
	if (!FIPv4Address::Parse(IP, IPAddress)) return false;

	TSharedRef<FInternetAddr> ServerAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	ServerAddr->SetIp(IPAddress.Value);
	ServerAddr->SetPort(Port);

	// Try to Connect
	UE_LOG(LogTemp, Display, TEXT("Connecting to Server %s:%d..."), *IP, Port);
	bool bConnected = Socket->Connect(*ServerAddr);

	if (bConnected)
	{
		Socket->SetNonBlocking(true);
		UE_LOG(LogTemp, Display, TEXT("Connect Success!"));
		FString TempID = "admin";
		LoginAccess(TempID, TempID);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Connect Failed!"));
		Disconnect();
	}

	return bConnected;
}

void ClientNetworking::Disconnect()
{
	if (Socket)
	{
		Socket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
		Socket = nullptr;
	}

	RecvBuffer.Empty();
}

bool ClientNetworking::SendPacket(uint16 PacketID, const void* Data, uint16 DataSize)
{
	if (!Socket) { return false; }

	// Create Send Buffer ( Header + Data )
	TArray<uint8> SendBuffer;
	uint16 BufferSize = sizeof(FPacketHeader) + DataSize;
	SendBuffer.SetNum(BufferSize);

	FPacketHeader* Header = reinterpret_cast<FPacketHeader*> (SendBuffer.GetData());
	Header->PacketID = PacketID;
	Header->PacketSize = BufferSize;

	if (DataSize > 0 && Data != nullptr) {
		FMemory::Memcpy(SendBuffer.GetData() + sizeof(FPacketHeader), Data, DataSize);
	}

	// Send Protocol
	int32 BytesSent = 0;
	return Socket->Send(SendBuffer.GetData(), SendBuffer.Num(), BytesSent);
}

void ClientNetworking::RecvPacketProcess()
{
	if (!Socket) { return; }

	// Check Data Input
	uint32 PendingDataSize = 0;
	if (Socket->HasPendingData(PendingDataSize) && PendingDataSize > 0) {
		TArray<uint8> TempBuffer;
		TempBuffer.SetNumUninitialized(PendingDataSize);

		int32 ReadBytes = 0;
		if (Socket->Recv(TempBuffer.GetData(), PendingDataSize, ReadBytes)) {
			RecvBuffer.Append(TempBuffer.GetData(), ReadBytes);
		}
	}

	//UE_LOG(LogTemp, Log, TEXT("Packet Recv Start!"));
	
	// Packet Assemble
	while (RecvBuffer.Num() >= sizeof(FPacketHeader)) {
		FPacketHeader* Header = reinterpret_cast<FPacketHeader*> (RecvBuffer.GetData());

		// Wait for next Tick if Data not filled PacketSize
		if (RecvBuffer.Num() < Header->PacketSize) { break; }

		//UE_LOG(LogTemp, Log, TEXT("[Packet Recv] Pakcet ID : %d / Packet SIZE : %d"), Header->PacketID, Header->PacketSize);

		/* Need Packet Process Logic */
		uint8* LoadData = RecvBuffer.GetData() + sizeof(FPacketHeader);
		PacketHandle(Header, LoadData);

		// Remove Processed Packet Size in front of Buffer
		RecvBuffer.RemoveAt(0, Header->PacketSize);
	}
}

void ClientNetworking::LoginAccess(FString& ID, FString& PW)
{
	// Need Input ID and PW Logic

	// --------------------------
	FBufferArchive data;
	data << ID; data << PW;
	TArray<uint8> packet = PacketAssemble(PKT_C2S_LOGIN, data);
	
	if (!Socket) { UE_LOG(LogTemp, Log, TEXT("Failed to Login")); return; }

	int32 SentBytes = 0;
	Socket->Send(packet.GetData(), packet.Num(), SentBytes);
	UE_LOG(LogTemp, Log, TEXT("Login Accessed"));
}

TArray<uint8> ClientNetworking::PacketAssemble(PacketID _id, const TArray<uint8> data)
{
	FBufferArchive ret = NULL;

	// declare Temp packets
	FPacketHeader Header;
	Header.PacketID = _id;
	
	Header.PacketSize = sizeof(FPacketHeader) + data.Num();

	ret.Append((uint8*)&Header, sizeof(FPacketHeader));

	if (data.Num() > 0) { ret.Append(data); }

	return ret;
}

void ClientNetworking::PacketHandle(FPacketHeader* Header, uint8* LoadData)
{
	uint16 LoadSize = Header->PacketSize - sizeof(FPacketHeader);

	switch (Header->PacketID)
	{
	case PKT_S2C_LOGIN_OK:
		PacketDeserialize(LoadData, LoadSize);
		UE_LOG(LogTemp, Display, TEXT("Login Successful!"));
		break;
	case PKT_S2C_SNAPSHOT:
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Wrong Packet Type! [ID: %d ]"), Header->PacketID);
		break;
	}
}

void ClientNetworking::PacketDeserialize(uint8* Data, uint16 DataSize)
{
	if (DataSize < sizeof(FGamedataPacket)) {
		UE_LOG(LogTemp, Error, TEXT("Pakcet Size mismatch! [Expected: %d | Received: %d]"),
			sizeof(FGamedataPacket), DataSize);
		return;
	}

	FGamedataPacket packet;
	FMemory::Memcpy(&packet, Data, sizeof(FGamedataPacket));

	int32 sessionID = packet.sessionID;
	int32 userID = packet.data.userUID;

	float X = packet.data.x; float Y = packet.data.y; float Z = packet.data.z;
}
