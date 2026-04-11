// Fill out your copyright notice in the Description page of Project Settings.
#include "ClientNetworking.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Engine/GameEngine.h"

ClientNetworking::ClientNetworking()
{
	Socket = nullptr;
	IsLogin = false;
}

ClientNetworking::~ClientNetworking()
{
	Disconnect();
}


bool ClientNetworking::IsConnected() const
{
	return Socket != nullptr && Socket->GetConnectionState() == SCS_Connected;
}

bool ClientNetworking::Connect(FString IP, int32 Port)
{
	// Disconnect If existing Connection exist
	Disconnect();

	// Create Socket
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
	
	if (!Socket) { return false; }
		
	// IP Address Parsing
	FIPv4Address IPAddress;
	
	if (!FIPv4Address::Parse(IP, IPAddress)) { return false; }

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
		
		// Connection Check
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Connect Successful to..."));
		
		// Login Info Set
		FString TempID = "admin";
		
		//LoginAccess(TempID, TempID);
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Fail to Connect..."));
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
	if (!Socket || Socket->GetConnectionState() != SCS_Connected) {
		// Call Delegate if Invalid Socket Connect
		if (OnDisconnected.IsBound()) { OnDisconnected.Broadcast(); }
		return false; 
	}

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
	if (!Socket || Socket->GetConnectionState() != SCS_Connected) {
		// Call Delegate if Invalid Socket Connect
		if (OnDisconnected.IsBound()) { OnDisconnected.Broadcast(); }
		return; 
	}


	// Check Data Input
	uint32 PendingDataSize = 0;
	if (Socket->HasPendingData(PendingDataSize) && PendingDataSize > 0) {
		TArray<uint8> TempBuffer;
		
		int32 SizeToRead = (PendingDataSize > 0) ? PendingDataSize : 1;
		TempBuffer.SetNumUninitialized(PendingDataSize);
		
		int32 ReadBytes = 0;


		// Socket Error: Return is false
		if (!Socket->Recv(TempBuffer.GetData(), PendingDataSize, ReadBytes)) {
			if (OnDisconnected.IsBound()) { OnDisconnected.Broadcast(); }
			return;
		}

		// General Shutdown: Return is True but Read 0 byte
		if (ReadBytes == 0) {
			if (OnDisconnected.IsBound()) { OnDisconnected.Broadcast(); }
			return;
		}

		if (ReadBytes > 0) { RecvBuffer.Append(TempBuffer.GetData(), ReadBytes); }
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
	FBufferArchive data;
	data << ID; data << PW;

	TArray<uint8> packet = PacketAssemble(PKT_C2S_LOGIN_REQ, data);

	if (!Socket) { UE_LOG(LogTemp, Log, TEXT("Failed to Login")); return; }
	
	int32 SentBytes = 0;
	Socket->Send(packet.GetData(), packet.Num(), SentBytes);
	UE_LOG(LogTemp, Log, TEXT("Login Accessed"));
}

void ClientNetworking::RegisterRequest(FString& ID, FString& PW)
{
	FBufferArchive data;
	data << ID; data << PW;

	TArray<uint8> packet = PacketAssemble(PKT_C2S_REGISTER_REQ, data);

	if (!Socket) { UE_LOG(LogTemp, Log, TEXT("Failed to Register")); return; }

	int32 SentBytes = 0;
	Socket->Send(packet.GetData(), packet.Num(), SentBytes);
	UE_LOG(LogTemp, Log, TEXT("Register Accessed"));
}

void ClientNetworking::CreateRoomRequest()
{
	TArray<uint8> emptyData;
	TArray<uint8> packet = PacketAssemble(PKT_C2S_ROOM_CREATE_REQ, emptyData);
	
	if (!Socket) {
		UE_LOG(LogTemp, Error, TEXT("Failed to Create Room - Socket is Invalid"));
		return;
	}

	int32 SentBytes = 0;
	Socket->Send(packet.GetData(), packet.Num(), SentBytes);
	UE_LOG(LogTemp, Log, TEXT("Create Room Requested to Server"));
}


void ClientNetworking::JoinRoomRequest(int32 RoomID)
{
	TArray<uint8> Payload;
	Payload.Append((uint8*)&RoomID, sizeof(int32));

	TArray<uint8> packet = PacketAssemble(PKT_C2S_ROOM_JOIN_REQ, Payload);
	
	if (!Socket) {
		UE_LOG(LogTemp, Error, TEXT("Failed to Join Room - Socket is Invalid"));
		return;
	}

	int32 SentBytes = 0;
	Socket->Send(packet.GetData(), packet.Num(), SentBytes);
	UE_LOG(LogTemp, Log, TEXT("Join Room Requested to Server"));
}

void ClientNetworking::ReadyToggleRequest()
{
	TArray<uint8> emptyData;
	TArray<uint8> packet = PacketAssemble(PKT_C2S_READY_REQ, emptyData);

	if (!Socket) { return; }

	int32 SentBytes = 0;
	Socket->Send(packet.GetData(), packet.Num(), SentBytes);
	UE_LOG(LogTemp, Log, TEXT("Ready Toggle Requested"));
}

void ClientNetworking::GameStartRequest()
{
	TArray<uint8> emptyData;
	TArray<uint8> packet = PacketAssemble(PKT_C2S_GAME_START_REQ, emptyData);

	if (!Socket) { return; }

	int32 SentBytes = 0;
	Socket->Send(packet.GetData(), packet.Num(), SentBytes);
	UE_LOG(LogTemp, Log, TEXT("Game Start Requested"));
}

//void ClientNetworking::RequestRoomList()
//{
//	TArray<uint8> emptyData;
//
//	TArray<uint8> packet = PacketAssemble(PKT_C2S_ROOM_LIST_REQ, emptyData);
//
//	if (!Socket) return;
//
//	int32 SentBytes = 0;
//	Socket->Send(packet.GetData(), packet.Num(), SentBytes);
//	UE_LOG(LogTemp, Log, TEXT("Requested Room List to Server"));
//}

TArray<uint8> ClientNetworking::PacketAssemble(PacketID _id, const TArray<uint8> data)
{
	FBufferArchive ret = NULL;

	// Declare Temp packets
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
	
	// Snapshot Temp Variable
	int32 UserCount = 0;
	FMemory::Memcpy(&UserCount, LoadData, sizeof(int32));
	TArray<GameData> SnapshotList;
	int32 Offset = sizeof(int32);
	GameData TempData;
	
	
	switch (Header->PacketID)
	{
	case PKT_S2C_ACCESS_ALLOW:
		UE_LOG(LogTemp, Display, TEXT("Sever Access Allow!"));
		break;
	case PKT_S2C_LOGIN_OK:
		PacketDeserialize(LoadData, LoadSize);
		if (OnLoginResult.IsBound()) { OnLoginResult.Broadcast(true); }
		UE_LOG(LogTemp, Display, TEXT("Login Successful!"));
		break;
	case PKT_S2C_LOGIN_DENY:
		PacketDeserialize(LoadData, LoadSize);
		OnLoginResult.Broadcast(false);
		UE_LOG(LogTemp, Display, TEXT("Login Failed!"));
		break;
	case PKT_S2C_REGISTER_OK:
		if (OnRegisterResult.IsBound()) { OnRegisterResult.Broadcast(true); }
		UE_LOG(LogTemp, Display, TEXT("Register Successful!"));
		break;
	case PKT_S2C_REGISTER_DENY:
		OnRegisterResult.Broadcast(false);
		UE_LOG(LogTemp, Display, TEXT("Register Failed!"));
		break;
	case PKT_S2C_SNAPSHOT_NOTICE:
		for (int32 i = 0; i < UserCount; ++i)
		{
			FMemory::Memcpy(&TempData, LoadData + Offset, sizeof(GameData));
			SnapshotList.Add(TempData);
			Offset += sizeof(GameData);
		}
		
		//UE_LOG(LogTemp, Display, TEXT("Snapshot Recive Completed! Current Num of Member: %d"), UserCount);
		break;
	case PKT_S2C_ROOM_UPDATE:
	{
		int32 RoomCount = 0;
		FMemory::Memcpy(&RoomCount, LoadData, sizeof(int32));
		TArray<FRoomInfoData> RoomList;
		int32 CurrentOffset = sizeof(int32);
		
		for (int32 i = 0; i < RoomCount; ++i)
		{
			FRoomPacketData RoomTempData;
			FMemory::Memcpy(&RoomTempData, LoadData + CurrentOffset, sizeof(FRoomPacketData));
			
			FRoomInfoData Info;
			Info.RoomID = RoomTempData.RoomID;
			Info.RoomName = FString(RoomTempData.RoomName);
			Info.CurrentPlayers = RoomTempData.CurrentPlayers;
			
			RoomList.Add(Info);

			CurrentOffset += sizeof(FRoomPacketData);
		}
		
		UE_LOG(LogTemp, Display, TEXT("Received Room List. Total: %d"), RoomCount);
		if (OnRoomListUpdated.IsBound()) {
			OnRoomListUpdated.Broadcast(RoomList);
		}
		break;
	}
	case PKT_S2C_ROOM_ENTER:
	{
		int32 CurrentOffset = 0;

		int32 EnteredRoomID = 0;
		FMemory::Memcpy(&EnteredRoomID, LoadData, sizeof(int32));
		CurrentOffset += sizeof(int32);

		int32 MemberCount = 0;
		FMemory::Memcpy(&MemberCount, LoadData + CurrentOffset, sizeof(int32));
		CurrentOffset += sizeof(int32);

		TArray<FRoomMemberInfo> PlayerList;
		for (int32 i = 0; i < MemberCount; ++i)
		{
			FRoomMemberPacketData MemberData;
			FMemory::Memcpy(&MemberData, LoadData + CurrentOffset, sizeof(FRoomMemberPacketData));
			CurrentOffset += sizeof(FRoomMemberPacketData);

			FRoomMemberInfo Info;
			Info.PlayerName = FString(MemberData.PlayerName);
			Info.bIsReady = MemberData.isReady;
			PlayerList.Add(Info);
		}

		UE_LOG(LogTemp, Display, TEXT("Room Enter Success! RoomID: %d"), EnteredRoomID);
		
		if (OnRoomEnterResult.IsBound()) {
			OnRoomEnterResult.Broadcast(true, PlayerList);
		}
		break;
	}
	case PKT_S2C_ROOM_INFO_BRD:
	{
		int32 CurrentOffset = 0;

		// [1] MemberCount 읽기
		int32 MemberCount = 0;
		FMemory::Memcpy(&MemberCount, LoadData + CurrentOffset, sizeof(int32));
		CurrentOffset += sizeof(int32);

		// [2] 멤버 리스트 읽기
		TArray<FRoomMemberInfo> PlayerList;
		for (int32 i = 0; i < MemberCount; ++i)
		{
			FRoomMemberPacketData MemberData;
			FMemory::Memcpy(&MemberData, LoadData + CurrentOffset, sizeof(FRoomMemberPacketData));
			CurrentOffset += sizeof(FRoomMemberPacketData);

			FRoomMemberInfo Info;
			Info.PlayerName = FString(MemberData.PlayerName);
			Info.bIsReady = MemberData.isReady;
			PlayerList.Add(Info);
		}

		UE_LOG(LogTemp, Display, TEXT("Room Info Updated! Members: %d"), MemberCount);

		// 기존 델리게이트 재활용 (bSuccess=true, 갱신된 멤버 리스트)
		if (OnRoomEnterResult.IsBound()) {
			OnRoomEnterResult.Broadcast(true, PlayerList);
		}
		break;
	}
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