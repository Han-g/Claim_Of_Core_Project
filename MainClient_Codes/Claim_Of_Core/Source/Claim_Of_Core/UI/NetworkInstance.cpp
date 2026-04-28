#include "NetworkInstance.h"

#include "Networking/ClientNetworking.h"
#include "LoginWidget.h"
#include "RobbyWidget.h"
#include "RoomWidget.h"
#include "Sub/MyCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Misc/PackageName.h"
#include "EngineUtils.h"

#include "GameState/InGame_GameState.h"

UNetworkInstance::UNetworkInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_BP(TEXT("/Game/Game/UI/WB_LoginMenu.WB_LoginMenu_C"));
	if (UI_BP.Succeeded()) {
		LoginWidgetClass = UI_BP.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> LOBBY_BP(TEXT("/Game/Game/UI/WB_Lobby.WB_Lobby_C"));
	if (LOBBY_BP.Succeeded()) {
		LobbyWidgetClass = LOBBY_BP.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> ROOM_BP(TEXT("/Game/Game/UI/WB_Room.WB_Room_C"));
	if (ROOM_BP.Succeeded()) {
		RoomWidgetClass = ROOM_BP.Class;
	}

	// Initial map Setting
	InGameLevel = TSoftObjectPtr<UWorld>(
		FSoftObjectPath(TEXT("/Game/Game/Map/Stage/BuildingStage.BuildingStage"))
	);
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

	// Bind delegates (all fire on game thread via PumpEvents)
	Client->OnConnected.AddUObject(this, &UNetworkInstance::HandleConnected);
	Client->OnConnectFailed.AddUObject(this, &UNetworkInstance::HandleConnectFailed);
	Client->OnDisconnected.AddUObject(this, &UNetworkInstance::HandleDisconnected);
	Client->OnRoomListUpdated.AddUObject(this, &UNetworkInstance::HandleRoomListUpdate);
	Client->OnRoomEnterResult.AddUObject(this, &UNetworkInstance::HandleRoomEnterResult);
	Client->OnLoginResult.AddUObject(this, &UNetworkInstance::HandleLoginResult);
	Client->OnRegisterResult.AddUObject(this, &UNetworkInstance::HandleRegisterResult);
	Client->OnGameStart.AddUObject(this, &UNetworkInstance::HandleGameStart);

	Client->OnSnapshotReceived.AddUObject(this, &UNetworkInstance::HandleSnapshotReceived);
	Client->OnAttackAction.AddUObject(this, &UNetworkInstance::HandleAttackActionReceived);
	Client->OnDamageApplied.AddUObject(this, &UNetworkInstance::HandleDamageApplied);
	Client->OnStatusUpdated.AddUObject(this, &UNetworkInstance::HandleStatusUpdated);
	Client->OnStateChanged.AddUObject(this, &UNetworkInstance::HandleStateChanged);
	Client->OnRespawned.AddUObject(this, &UNetworkInstance::HandleRespawned);

	// Start worker thread + connect
	Client->Start(ServerIPAddress, 9000);

	UE_LOG(LogTemp, Display, TEXT("Initalize successfully!"));
}

void UNetworkInstance::Shutdown()
{
	if (Client.IsValid())
	{
		Client->Shutdown();
		Client.Reset();
	}
	Super::Shutdown();
}

void UNetworkInstance::Tick(float DeltaTime)
{
	// Drain worker events → fire delegates on game thread
	if (Client.IsValid())
	{
		Client->PumpEvents();
		if (bHasPendingSnapshot && PendingSnapshotList.Num() > 0 && 
			UGameplayStatics::GetPlayerCharacter(this, 0)) {
			HandleSnapshotReceived(PendingSnapshotList);
			bHasPendingSnapshot = false;
			PendingSnapshotList.Empty();
		}
	}
}

int32 UNetworkInstance::GetPlayerUID() const { return Client.IsValid() ? Client->ClientPlayerData.userUID : -1; }

void UNetworkInstance::SelectCharacterAndReady(int32 SelectedRoleType)
{
	CachedSelectedRoleType = SelectedRoleType;

	UE_LOG(LogTemp, Display, TEXT("[CharacterSelect] Role=%d clicked"), SelectedRoleType);

	if (!Client.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[CharacterSelect] Client invalid"));
		return;
	}

	if (bReadySent)
	{
		UE_LOG(LogTemp, Display, TEXT("[CharacterSelect] Ready already sent for this room"));
		return;
	}

	RequestReady();
	bReadySent = true;

	UE_LOG(LogTemp, Display, TEXT("[CharacterSelect] Ready request sent"));
}

void UNetworkInstance::ShowLoginHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("Called ShowLoginHUD Function!"));

	if (LoginWidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cause: LoginWidgetClass is Empty! (Not allocation)"));
		return;
	}

	/*if (LoginWidgetClass && !LoginWidgetInstance)
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
	}*/
	
	if (!LoginWidgetInstance)
	{
		LoginWidgetInstance = CreateWidget<UUserWidget>(this, LoginWidgetClass);
		if (!LoginWidgetInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create LoginWidgetInstance"));
			return;
		}

		LoginWidgetInstance->AddToViewport();
	}

	if (APlayerController* PC = GetFirstLocalPlayerController())
	{
		UE_LOG(LogTemp, Display, TEXT("Check PlayerController Test"));
		PC->SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController Cant Find!"));
		return;
	}

	// 실제 포커스는 루트 위젯이 아니라 로그인 입력창에 준다.
	if (ULoginWidget* LoginUI = Cast<ULoginWidget>(LoginWidgetInstance))
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimerForNextTick([LoginUI]()
				{
					if (LoginUI)
					{
						LoginUI->FocusInitialWidget();
					}
				});
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

void UNetworkInstance::CharacterSelectRequest()
{
	if (!Client.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("[CharacterSelect] Client invalid"));
		return;
	}
	if (CachedSelectedRoleType < 0 || CachedSelectedRoleType > 2) {
		UE_LOG(LogTemp, Warning, TEXT("[CharacterSelect] Invalid cached role: %d"), CachedSelectedRoleType);
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("[CharacterSelect] Request sent. Role=%d"),
		CachedSelectedRoleType);
}

void UNetworkInstance::RequestReady()
{
	if (Client.IsValid()) {
		Client->CharacterSelectRequest(CachedSelectedRoleType);
		Client->ReadyToggleRequest();
	}
}

void UNetworkInstance::RequestGameStart()
{
	if (Client.IsValid()) {
		Client->GameStartRequest();
	}
}

void UNetworkInstance::SendMoveInputToServer(const FMovePacket& MoveData)
{
	if (!Client.IsValid()) { return; }

	Client->SendMoveInput(MoveData);
}

void UNetworkInstance::SendGameplayTestPacket(PacketID TestPacket)
{
	if (!Client.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[ClientTest] Client is invalid."));
		return;
	}

	Client->TestFuncInput(TestPacket);
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

		if (LobbyWidgetClass && !LobbyWidgetInstance) {
			LobbyWidgetInstance = CreateWidget<UUserWidget>(this, LobbyWidgetClass);

			if (LobbyWidgetInstance) {
				LobbyWidgetInstance->AddToViewport();
				APlayerController* PC = GetFirstLocalPlayerController();

				if (PC) {
					PC->SetShowMouseCursor(true);

					FInputModeUIOnly InputMode;
					//InputMode.SetWidgetToFocus(LobbyWidgetInstance->TakeWidget());
					InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

					PC->SetInputMode(InputMode);

					UE_LOG(LogTemp, Display, TEXT("[ClientLoginSync] SessionID=%d UID=%d"),
						Client->ClientSessionID,
						Client->ClientPlayerData.userUID);
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

void UNetworkInstance::HandleRoomEnterResult(bool bSuccess, const TArray<FRoomMemberInfo>& playerList)
{
	if (!bSuccess) { return; }

	const bool bFirstEnter = (RoomWidgetInstance == nullptr);

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

	if (bFirstEnter) {
		bReadySent = false;
		CachedSelectedRoleType = -1;
	}

	if (RoomWidgetInstance)
	{
		RoomWidgetInstance->UpdateMemberList(playerList);
	}
}

void UNetworkInstance::HandleGameStart()
{
	UE_LOG(LogTemp, Display, TEXT("Game Starting! Closing Room Widget."));

	if (RoomWidgetInstance) {
		RoomWidgetInstance->RemoveFromParent();
		RoomWidgetInstance = nullptr;
	}

	/* Game Start For Change GameState
	APlayerController* PC = GetFirstLocalPlayerController();
	if (PC) {
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}

	if (UWorld* World = GetWorld()) {
		if (AInGame_GameState* GS = World->GetGameState<AInGame_GameState>()) {
			GS->ActivateGameplayFromServerStart();
		}
	}*/


	// Game Start For Change Ingame Level
	if (!InGameLevel.IsNull())
	{
		APlayerController* PC = GetFirstLocalPlayerController();
		if (PC) {
			PC->SetShowMouseCursor(false);
			PC->SetInputMode(FInputModeGameOnly());
		}

		const FName LevelName =
			FName(*FPackageName::ObjectPathToPackageName(InGameLevel.ToString()));
		UE_LOG(LogTemp, Display, TEXT("Opening InGame Level: %s"), *LevelName.ToString());

		bHasPendingSnapshot = false;
		PendingSnapshotList.Empty();

		bLocalInitialTransformApplied = false;
		UGameplayStatics::OpenLevel(this, LevelName);
		// 레벨 전환 후 입력 모드는 새 PlayerController의 BeginPlay에서 설정하는 게 자연스러움
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InGameLevel is not set in NetworkInstance!"));
	}
}

void UNetworkInstance::HandleConnected()
{
	UE_LOG(LogTemp, Display, TEXT("Connected to server! Showing login HUD."));
	RetryCounter = 0;
	ShowLoginHUD();
}

void UNetworkInstance::HandleConnectFailed()
{
	UE_LOG(LogTemp, Error, TEXT("Failed to connect to server."));
}

void UNetworkInstance::HandleDisconnected()
{
	UE_LOG(LogTemp, Warning, TEXT("Disconnected from server. Requesting reconnect..."));

	if (Client.IsValid())
	{
		Client->RequestReconnect();
	}
}

void UNetworkInstance::HandleSnapshotReceived(const TArray<GameData>& SnapshotList)
{
	if (!Client.IsValid()) { return; }
	if (SnapshotList.Num() <= 0) { return; }

	const int32 LocalUID = Client->ClientPlayerData.userUID;
	AMyCharacter* LocalCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!LocalCharacter) {
		PendingSnapshotList = SnapshotList;
		bHasPendingSnapshot = true;

		UE_LOG(LogTemp, Warning, TEXT("[Snapshot] Local character not ready. Snapshot cached."));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("[SnapshotUID] LocalUID=%d Count=%d"), LocalUID, SnapshotList.Num());

	for (const GameData& Data : SnapshotList)
	{
		if (Data.userUID <= 0) { continue; }
		/*UE_LOG(LogTemp, Display, TEXT("[SnapshotUID] DataUID=%d Pos=(%.1f, %.1f, %.1f) Role=%d"),
			Data.userUID, Data.x, Data.y, Data.z, Data.roleType);*/

		if (Data.userUID == LocalUID)
		{
			if (!LocalCharacter) { continue; }

			LocalCharacter->SetNetworkPlayerUID(LocalUID);
			LocalCharacter->SetRoleFromNetwork(Data.roleType);
			LocalCharacter->SetHPFromNetwork(Data.currentHP);
			LocalCharacter->SetStateFromNetwork(Data.characterState);
			
			if (!bLocalInitialTransformApplied)
			{
				LocalCharacter->ApplyTransformFromNetwork(Data.x, Data.y, Data.z, Data.rotate);
				bLocalInitialTransformApplied = true;
			}
		}
		else
		{
			AMyCharacter* RemoteCharacter = EnsureRemoteCharacter(Data);
			if (!RemoteCharacter) { continue; }

			RemoteCharacter->SetNetworkPlayerUID(Data.userUID);
			RemoteCharacter->SetRoleFromNetwork(Data.roleType);
			RemoteCharacter->SetHPFromNetwork(Data.currentHP);
			RemoteCharacter->SetStateFromNetwork(Data.characterState);
			RemoteCharacter->ApplyTransformFromNetwork(Data.x, Data.y, Data.z, Data.rotate);
			RemoteCharacter->SetAnimationFromNetwork(Data.animationNum);
		}
	}
}

void UNetworkInstance::HandleAttackActionReceived(const FAttackActionPacket& Packet)
{
	UE_LOG(LogTemp, Display,
		TEXT("[ClientTest] HandleAttackActionReceived: Attacker=%d Type=%d"),
		Packet.AttackerID,
		Packet.AttackType);

	UWorld* World = GetWorld();
	if (!World) { return; }

	for (TActorIterator<AMyCharacter> It(World); It; ++It)
	{
		AMyCharacter* Character = *It;
		UE_LOG(LogTemp, Display,
			TEXT("[AttackUID] Check Character=%s CharacterUID=%d PacketAttackerID=%d"),
			Character ? *Character->GetName() : TEXT("NULL"),
			Character ? Character->GetNetworkPlayerUID() : -999,
			Packet.AttackerID);

		if (!Character || Character->GetNetworkPlayerUID() != Packet.AttackerID)
		{
			continue;
		}

		UE_LOG(LogTemp, Display,
			TEXT("[AttackUID] Matched. Play montage. Character=%s"),
			*Character->GetName());

		Character->PlayAttackMontageFromServer(Packet.AttackType);
		break;
	}
}

void UNetworkInstance::HandleDamageApplied(const FDamageApplyPacket& Packet)
{
	const int32 LocalUID = Client.IsValid() ? Client->ClientPlayerData.userUID : -1;
	const bool bIsLocalTarget = (Packet.TargetID == LocalUID);

	UE_LOG(LogTemp, Display,
		TEXT("[ClientTest] HandleDamageApplied: Target=%d Damage=%d RemainHP=%d LocalTarget=%s"),
		Packet.TargetID,
		Packet.Damage,
		Packet.RemainHP,
		bIsLocalTarget ? TEXT("true") : TEXT("false"));
}

void UNetworkInstance::HandleStatusUpdated(const FStatusUpdatePacket& Packet)
{
	if (AMyCharacter* Character = FindCharacterByUID(Packet.TargetID))
	{
		Character->SetHPFromNetwork(Packet.CurrentHP);
	}
}

void UNetworkInstance::HandleStateChanged(const FStateChangePacket& Packet)
{
	if (AMyCharacter* Character = FindCharacterByUID(Packet.TargetID))
	{
		Character->SetStateFromNetwork(Packet.NewState);
	}
}

void UNetworkInstance::HandleRespawned(const FRespawnPacket& Packet)
{
	if (AMyCharacter* Character = FindCharacterByUID(Packet.TargetID))
	{
		Character->SetHPFromNetwork(Packet.HP);
		Character->SetStateFromNetwork(0);
		Character->ApplyTransformFromNetwork(Packet.X, Packet.Y, Packet.Z, Character->GetActorRotation().Yaw);
	}
}

AMyCharacter* UNetworkInstance::FindCharacterByUID(int32 UID) const
{
	if (UID <= 0) { return nullptr; }

	if (const TWeakObjectPtr<AMyCharacter>* Found = RemoteCharacters.Find(UID)) {
		if (Found->IsValid()) { return Found->Get(); }
	}

	UWorld* World = GetWorld();
	if (!World) { return nullptr; }

	for (TActorIterator<AMyCharacter> It(World); It; ++It) {
		AMyCharacter* Character = *It;
		if (Character && Character->GetNetworkPlayerUID() == UID) {
			return Character;
		}
	}

	return nullptr;
}

AMyCharacter* UNetworkInstance::EnsureRemoteCharacter(const GameData& Data)
{
	if (TWeakObjectPtr<AMyCharacter>* Found = RemoteCharacters.Find(Data.userUID)) {
		if (Found->IsValid()) {
			return Found->Get();
		}
	}

	if (!RemoteCharacterClass) {
		UE_LOG(LogTemp, Error, TEXT("RemoteCharacterClass is not set."));
		return nullptr;
	}

	UWorld* World = GetWorld();
	if (!World) { return nullptr; }

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMyCharacter* NewCharacter = World->SpawnActor<AMyCharacter>(
		RemoteCharacterClass,
		FVector(Data.x, Data.y, Data.z),
		FRotator(0.f, Data.rotate, 0.f),
		Params);

	if (!NewCharacter) { return nullptr; }

	NewCharacter->SetNetworkPlayerUID(Data.userUID);
	RemoteCharacters.Add(Data.userUID, NewCharacter);

	return NewCharacter;
}
