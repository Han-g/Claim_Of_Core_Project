// Fill out your copyright notice in the Description page of Project Settings.
#include "NetworkInstance.h"
#include "ClientNetworking.h"
#include "LoginWidget.h"
#include "RobbyWidget.h"
#include "RoomWidget.h"

UNetworkInstance::UNetworkInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_BP(TEXT("/Game/UI/WB_LoginMenu.WB_LoginMenu_C"));
	if (UI_BP.Succeeded()) {
		LoginWidgetClass = UI_BP.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> LOBBY_BP(TEXT("/Game/UI/WB_Lobby.WB_Lobby_C"));
	if (LOBBY_BP.Succeeded()) {
		LobbyWidgetClass = LOBBY_BP.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> ROOM_BP(TEXT("/Game/UI/WB_Room.WB_Room_C"));
	if (ROOM_BP.Succeeded()) {
		RoomWidgetClass = ROOM_BP.Class;
	}
}

void UNetworkInstance::Init()
{
	UE_LOG(LogTemp, Display, TEXT("Initalization Start!"));
	Super::Init();

	Client = MakeShared<ClientNetworking>();

	if (GConfig) {
		GConfig->GetString(
			TEXT("ServerSettings"),
			TEXT("ServerIP"),
			ServerIPAddress,
			GGameIni
		);
	}


	// Bind Connect maintenance Logic
	Client->OnRoomListUpdated.AddUObject(this, &UNetworkInstance::HandleRoomListUpdate);
	Client->OnRoomEnterResult.AddUObject(this, &UNetworkInstance::HandleRoomEnterResult);
	Client->OnDisconnected.AddUObject(this, &UNetworkInstance::ConnectionLost);
	Client->OnLoginResult.AddUObject(this, &UNetworkInstance::HandleLoginResult);
	Client->OnRegisterResult.AddUObject(this, &UNetworkInstance::HandleRegisterResult);
	
	if (ServerIPAddress.Equals(TEXT("127.0.0.1"), ESearchCase::IgnoreCase)) {
		UE_LOG(LogTemp, Display, TEXT("Connecting to localhost"));
		Client->Connect(ServerIPAddress, 9000); // Localhost Test
	}

	else {
		UE_LOG(LogTemp, Display, TEXT("Connecting to IP: %s"), *ServerIPAddress);
		Client->Connect(ServerIPAddress, 9000);
	}

	// Check Reception every 0.01 sec
	//GetWorld()->GetTimerManager().SetTimer(NetworkTimer, this, &UNetworkInstance::CheckNetwork, 0.01f, true);
	UE_LOG(LogTemp, Display, TEXT("Initalize successfully!"));
	//ShowLoginHUD();
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

void UNetworkInstance::ShowLoginHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("Called ShowLoginHUD Function!"));
	
	if (LoginWidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cause: LoginWidgetClass is Empty! (Not allocation)"));
		return;
	}

	if (LoginWidgetClass && !LoginWidgetInstance)
	{
		LoginWidgetInstance = CreateWidget<UUserWidget>(this, LoginWidgetClass);
		if (LoginWidgetInstance)
		{
			LoginWidgetInstance->AddToViewport();
			
			APlayerController* PC = GetFirstLocalPlayerController();
			if (PC) {
				PC->SetShowMouseCursor(true);
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(LoginWidgetInstance->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PC->SetInputMode(InputMode);
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("PlayerController Cant Find!"));
			}
		}
	}
}

void UNetworkInstance::TryLogin(FString ID, FString PW)
{
	if (Client.IsValid()) {
		Client->LoginAccess(ID, PW);
	}
}

void UNetworkInstance::TryRegister(FString ID, FString PW)
{
	if (Client.IsValid()) {
		Client->RegisterRequest(ID, PW);
	}
}

void UNetworkInstance::CreateRoom()
{
	if (Client.IsValid()) {
		Client->CreateRoomRequest();
	}
}

void UNetworkInstance::JoinRoom(int32 RoomID)
{
	if (Client.IsValid()) {
		Client->JoinRoomRequest(RoomID);
	}
}

void UNetworkInstance::HandleLoginResult(bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Display, TEXT("Login Successful! Close Widget."));
		
		if (LoginWidgetInstance) {
			LoginWidgetInstance->RemoveFromParent();
			LoginWidgetInstance = nullptr;
		}

		/*APlayerController* PC = GetFirstLocalPlayerController();
		if (PC) {
			PC->SetShowMouseCursor(false);
			PC->SetInputMode(FInputModeGameOnly());
		}*/

		if (LobbyWidgetClass && !LobbyWidgetInstance) {
			LobbyWidgetInstance = CreateWidget<UUserWidget>(this, LobbyWidgetClass);
			
			if (LobbyWidgetInstance) {
				LobbyWidgetInstance->AddToViewport();
				APlayerController* PC = GetFirstLocalPlayerController();
				
				if (PC) {
					PC->SetShowMouseCursor(true);
					
					FInputModeUIOnly InputMode;
					InputMode.SetWidgetToFocus(LobbyWidgetInstance->TakeWidget());
					InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
					
					PC->SetInputMode(InputMode);
				}
			}
		}
		else if (LobbyWidgetClass == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("LobbyWidgetClass is Not Assignment, Check Blueprinter."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Login Failed! Wrong Account Info."));
		
		// Call function Pop up Window
		if (LoginWidgetInstance) {
			ULoginWidget* LoginUI = Cast<ULoginWidget>(LoginWidgetInstance);
			if (LoginUI) { LoginUI->ShowPopup(FText::FromString(TEXT("Login Failed!"))); }
		}
	}
}

void UNetworkInstance::HandleRegisterResult(bool bSuccess)
{
	if (LoginWidgetInstance) {
		ULoginWidget* LoginUI = Cast<ULoginWidget>(LoginWidgetInstance);
		
		if (LoginUI) {
			if (bSuccess) {
				LoginUI->ShowPopup(FText::FromString(TEXT("Register Successful!")));
			}
			else {
				LoginUI->ShowPopup(FText::FromString(TEXT("Register Failed! (Duplicate ID)")));
			}
		}
	}
}

void UNetworkInstance::HandleRoomListUpdate(const TArray<FRoomInfoData>& RoomList)
{
	if (LobbyWidgetInstance) {
		URobbyWidget* RobbyUI = Cast<URobbyWidget>(LobbyWidgetInstance);
		
		if (RobbyUI) {
			RobbyUI->ReloadRoomList(RoomList);
		}
	}
}

void UNetworkInstance::HandleRoomEnterResult(bool bSuccess, const TArray<FString>& PlayerList)
{
	if (!bSuccess) { return; }

	if (LobbyWidgetInstance) {
		LobbyWidgetInstance->RemoveFromParent();
		LobbyWidgetInstance = nullptr;
	}

	if (RoomWidgetClass && !RoomWidgetInstance) {
		RoomWidgetInstance = CreateWidget<URoomWidget>(this, RoomWidgetClass);
		if (RoomWidgetInstance) {
			RoomWidgetInstance->AddToViewport();
		}
	}

	if (RoomWidgetInstance)
	{
		URoomWidget* RoomMemberUI = Cast<URoomWidget>(RoomWidgetInstance);
		
		if (RoomMemberUI) {
			RoomMemberUI->UpdateMemberList(PlayerList);
		}
	}
}

void UNetworkInstance::ConnectionLost()
{
	UE_LOG(LogTemp, Warning, TEXT("Connection Lost detected via Delegate!"));
	if (GetWorld()->GetTimerManager().IsTimerActive(ReconnectTimer)) return;
	RetryCounter = 0;
	
	TryReconnect();
}

void UNetworkInstance::TryReconnect()
{
	if (RetryCounter >= MaxRetryCount)
	{
		UE_LOG(LogTemp, Error, TEXT("Lost Connection to Game Server."));
		return;
	}

	RetryCounter++;
	UE_LOG(LogTemp, Warning, TEXT("Reconnecting attempt... (%d/%d)"), RetryCounter, MaxRetryCount);
	
	GetWorld()->GetTimerManager().SetTimer(ReconnectTimer, [this]()
		{
			if (Client.IsValid()) { Client->Disconnect(); }
			
			bool bSuccess = Client->Connect(ServerIPAddress, 9000);
			
			if (bSuccess)
			{
				UE_LOG(LogTemp, Display, TEXT("Reconnection Successful!"));
				RetryCounter = 0;
			}
			else
			{
				TryReconnect();
			}
		}, 3.0f, false);
}