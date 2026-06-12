// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkInstance.h"

#include "ClientNetworking.h"

void UNetworkInstance::Init()
{
	UE_LOG(LogTemp, Display, TEXT("Initalization Start!"));
	Super::Init();

	Client = MakeShared<ClientNetworking>();
	Client->Connect(TEXT("127.0.0.1"), 9000); // Localhost Test

	// Check Reception every 0.01 sec
	//GetWorld()->GetTimerManager().SetTimer(NetworkTimer, this, &UNetworkInstance::CheckNetwork, 0.01f, true);
	UE_LOG(LogTemp, Display, TEXT("Initalize successfully!"));
}

void UNetworkInstance::Shutdown()
{
	if (Client.IsValid()) { Client->Disconnect(); Client.Reset(); }

	Super::Shutdown();
}

void UNetworkInstance::Tick(float DeltaTime)
{
	// Try to Login
	//FString TempID = "admin"; -> Add Input ID and PW Logic
	//if (!Client->IsLogin) { 
	//	//Client->LoginAccess(TempID, TempID); 
	//	UE_LOG(LogTemp, Display, TEXT("INVAILD LOGIN ACCESS!"));
	//}

	// Sync with Server
	if (Client.IsValid()) { Client->RecvPacketProcess(); }
	
	//UE_LOG(LogTemp, Display, TEXT("Tick"));
	// Game Data Send
}
