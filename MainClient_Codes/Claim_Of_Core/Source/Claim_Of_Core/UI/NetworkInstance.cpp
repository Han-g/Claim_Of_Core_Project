#include "NetworkInstance.h"

#include "Networking/ClientNetworking.h"
#include "LoginWidget.h"
#include "RobbyWidget.h"
#include "RoomWidget.h"
#include "BaseItem.h"
#include "Map/Building/SmallDebrisActor.h"
#include "Map/Building/LargeDebrisController.h"
#include "Map/IceCave/IceFloorTile.h"
#include "Map/IceCave/IceChillZone.h"
#include "Map/Space/BlackHoleActor.h"
#include "Sub/MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Misc/PackageName.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

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
			TEXT("LocalServerIP"),
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

	Client->OnMapSelected.AddUObject(this, &UNetworkInstance::HandleMapSelected);
	Client->OnSnapshotReceived.AddUObject(this, &UNetworkInstance::HandleSnapshotReceived);
	Client->OnAttackAction.AddUObject(this, &UNetworkInstance::HandleAttackActionReceived);
	Client->OnDamageApplied.AddUObject(this, &UNetworkInstance::HandleDamageApplied);
	Client->OnStatusUpdated.AddUObject(this, &UNetworkInstance::HandleStatusUpdated);
	Client->OnStateChanged.AddUObject(this, &UNetworkInstance::HandleStateChanged);
	Client->OnRespawned.AddUObject(this, &UNetworkInstance::HandleRespawned);
	Client->OnGameTimeSynced.AddUObject(this, &UNetworkInstance::HandleGameTimeSynced);
	Client->OnPhaseChanged.AddUObject(this, &UNetworkInstance::HandlePhaseChanged);
	Client->OnMapEventTriggered.AddUObject(this, &UNetworkInstance::HandleMapEventTriggered);
	Client->OnObjectSpawned.AddUObject(this, &UNetworkInstance::HandleObjectSpawned);
	Client->OnItemOwnershipChanged.AddUObject(this, &UNetworkInstance::HandleItemOwnershipChanged);
	
	Client->OnStatusEffect.AddUObject(this, &UNetworkInstance::HandleStatusEffect);
	Client->OnItemSpawned.AddUObject(this, &UNetworkInstance::HandleItemSpawned);
	
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

void UNetworkInstance::StartClientOnlyTestFlow()
{
	bClientOnlyTestMode = true;

	if (!Client.IsValid())
	{
		Client = MakeShared<ClientNetworking>();
	}

	Client->ClientSessionID = 1;
	Client->ClientPlayerData.userUID = 1001;
	Client->ClientPlayerData.roleType = 1;
	Client->ClientPlayerData.currentHP = 100;
	Client->IsLogin = true;

	TArray<FRoomMemberInfo> FakeList;
	FRoomMemberInfo MyInfo;
	MyInfo.PlayerName = TEXT("LocalTestPlayer");
	MyInfo.bIsReady = false;
	FakeList.Add(MyInfo);

	// TEST FLOW
	ShowLoginHUD();
	HandleLoginResult(true);
	HandleRoomEnterResult(true, FakeList);
	SelectCharacterAndReady(1);
	HandleGameStart();

	TArray<GameData> FakeSnapshot;
	GameData LocalData;
	LocalData.userUID = Client->ClientPlayerData.userUID;
	LocalData.isConnected = true;
	LocalData.roleType = 1;
	LocalData.currentHP = 100;
	LocalData.characterState = 0;
	LocalData.x = 0.f;
	LocalData.y = 0.f;
	LocalData.z = 100.f;
	LocalData.rotate = 0.f;
	FakeSnapshot.Add(LocalData);

	HandleSnapshotReceived(FakeSnapshot);
}

void UNetworkInstance::Tick(float DeltaTime)
{
	// Drain worker events → fire delegates on game thread
	if (Client.IsValid())
	{
		Client->PumpEvents();

		/*if (bHasPendingSnapshot && PendingSnapshotList.Num() > 0 && 
			UGameplayStatics::GetPlayerCharacter(this, 0)) {
			HandleSnapshotReceived(PendingSnapshotList);
			bHasPendingSnapshot = false;
			PendingSnapshotList.Empty();
		}*/
		if (bPendingInitialSpawnLock && !bLocalInitialTransformApplied)
		{
			AMyCharacter* LocalCharacter =
				Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

			if (LocalCharacter && !bLocalSpawnLockApplied)
			{
				LocalCharacter->LockUntilInitialSnapshot();
				bLocalSpawnLockApplied = true;

				UE_LOG(LogTemp, Display,
					TEXT("[SpawnLock] Local character locked until first snapshot"));
			}
		}

		if (bHasPendingSnapshot && PendingSnapshotList.Num() > 0 &&
			UGameplayStatics::GetPlayerCharacter(this, 0))
		{
			HandleSnapshotReceived(PendingSnapshotList);
			bHasPendingSnapshot = false;
			PendingSnapshotList.Empty();
		}
	}
}

int32 UNetworkInstance::GetPlayerUID() const { return Client.IsValid() ? Client->ClientPlayerData.userUID : -1; }

void UNetworkInstance::SelectCharacterAndReady(int32 SelectedRoleType)
{
	if (SelectedRoleType < 0 || SelectedRoleType > 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("[CharacterSelect] Invalid role: %d"), SelectedRoleType);
		return;
	}

	CachedSelectedRoleType = SelectedRoleType;

	UE_LOG(LogTemp, Display, TEXT("[CharacterSelect] Role=%d clicked"), SelectedRoleType);

	if (!Client.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[CharacterSelect] Client invalid"));
		return;
	}

	Client->CharacterSelectRequest(CachedSelectedRoleType);

	if (!bReadySent)
	{
		//RequestReady();
		Client->ReadyToggleRequest();
		bReadySent = true;
	}

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
		TWeakObjectPtr<ULoginWidget> WeakLoginUI = LoginUI;

		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimerForNextTick([WeakLoginUI]()
				{
					if (ULoginWidget* SafeLoginUI = WeakLoginUI.Get())
					{
						SafeLoginUI->FocusInitialWidget();
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

void UNetworkInstance::RequestCharacterSelect()
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

void UNetworkInstance::RequestAttackInput(int32 AttackType)
{
	if (!Client.IsValid())
	{
		return;
	}

	if (!bClientOnlyTestMode)
	{
		SendGameplayAttackPacket(PKT_C2S_ATTACK_KEYINPUT);
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("[ClientTest] Send test packet: %d"), PKT_C2S_ATTACK_KEYINPUT);
	DispatchTestAttackAction(AttackType);
}

void UNetworkInstance::RequestAttackHitReport(uint32 AttackSeq, int32 TargetID, int32 AttackType)
{
	if (!Client.IsValid())
	{
		return;
	}

	if (AttackSeq == 0 || TargetID <= 0)
	{
		return;
	}

	Client->AttackHitReportRequest(AttackSeq, TargetID, AttackType);
}

void UNetworkInstance::RequestJumpInput()
{
	if (!Client.IsValid()) { return; }

	Client->SendJumpInput();
}

void UNetworkInstance::RequestItemPickup(int32 ItemID)
{
	if (!Client.IsValid()) { return; }

	if (ItemID < 0) { return; }

	Client->ItemPickupRequest(ItemID);
}

void UNetworkInstance::RequestItemDrop(int32 ItemID)
{ 
	if (!Client.IsValid()) { return; }

	if (ItemID < 0) { return; }

	Client->ItemDropRequest(ItemID);
}

void UNetworkInstance::RequestIceFloorStanding(int32 FloorID, int32 PieceIndex)
{
	if (!Client.IsValid() || PieceIndex < 0)
	{
		return;
	}

	Client->IceFloorStandRequest(FloorID, PieceIndex);
}

void UNetworkInstance::SendMoveInputToServer(const FMovePacket& MoveData)
{
	if (!Client.IsValid()) { return; }

	Client->SendMoveInput(MoveData);
}

void UNetworkInstance::SendGameplayAttackPacket(PacketID TestPacket)
{
	if (!Client.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[ClientTest] Client is invalid."));
		return;
	}

	Client->TestFuncInput(TestPacket);
}

void UNetworkInstance::DispatchTestAttackAction(int32 AttackType)
{
	const int32 LocalUID = Client->ClientPlayerData.userUID;
	if (LocalUID <= 0)
	{
		return;
	}

	FAttackActionPacket Packet{};
	Packet.AttackerID = LocalUID;
	Packet.AttackType = AttackType;

	HandleAttackActionReceived(Packet);
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
		bPendingInitialSpawnLock = true;
		bLocalSpawnLockApplied = false;

		MarkPendingGameplayActivation();
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

void UNetworkInstance::HandleMapSelected(int32 MapType)
{
	switch (MapType)
	{
	case 1:
		InGameLevel = TSoftObjectPtr<UWorld>(
			FSoftObjectPath(TEXT("/Game/Game/Map/Stage/BuildingStage.BuildingStage"))
		);
		break;

	case 2:
		InGameLevel = TSoftObjectPtr<UWorld>(
			FSoftObjectPath(TEXT("/Game/Game/Map/Stage/IceCaveStage.IceCaveStage"))
		);
		break;

	case 3:
		InGameLevel = TSoftObjectPtr<UWorld>(
			FSoftObjectPath(TEXT("/Game/Game/Map/Stage/SpaceStationStage.SpaceStationStage"))
		);
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown MapType: %d. Fallback to BuildingStage"), MapType);
		InGameLevel = TSoftObjectPtr<UWorld>(
			FSoftObjectPath(TEXT("/Game/Game/Map/Stage/BuildingStage.BuildingStage"))
		);
		break;
	}

	UE_LOG(LogTemp, Display, TEXT("Selected InGameLevel: %s"), *InGameLevel.ToString());
}

void UNetworkInstance::HandleSnapshotReceived(const TArray<GameData>& SnapshotList)
{
	if (!Client.IsValid()) { return; }
	if (SnapshotList.Num() <= 0) { return; }

	const int32 LocalUID = Client->ClientPlayerData.userUID;
	AMyCharacter* LocalCharacter = 
		Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	if (!LocalCharacter) {
		PendingSnapshotList = SnapshotList;
		bHasPendingSnapshot = true;

		//UE_LOG(LogTemp, Warning, TEXT("[Snapshot] Local character not ready. Snapshot cached."));
		return;
	}
	//UE_LOG(LogTemp, Display, TEXT("[SnapshotUID] LocalUID=%d Count=%d"), LocalUID, SnapshotList.Num());

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

				if (bPendingInitialSpawnLock || bLocalSpawnLockApplied)
				{
					LocalCharacter->UnlockAfterInitialSnapshot();
					bPendingInitialSpawnLock = false;
					bLocalSpawnLockApplied = false;

					UE_LOG(LogTemp, Display,
						TEXT("[SpawnLock] Released after first snapshot. Pos=(%.1f, %.1f, %.1f)"),
						Data.x, Data.y, Data.z);
				}
			}
			else
			{
				LocalCharacter->ApplyLocalServerCorrection(Data.x, Data.y, Data.z, Data.rotate);
			}
		}
		else
		{
			AMyCharacter* RemoteCharacter = EnsureRemoteCharacter(Data);
			if (!RemoteCharacter) { continue; }
			const FVector Before = RemoteCharacter->GetActorLocation();

			RemoteCharacter->SetNetworkPlayerUID(Data.userUID);
			RemoteCharacter->SetRoleFromNetwork(Data.roleType);
			RemoteCharacter->SetHPFromNetwork(Data.currentHP);
			RemoteCharacter->SetStateFromNetwork(Data.characterState);
			RemoteCharacter->ApplyTransformFromNetwork(Data.x, Data.y, Data.z, Data.rotate);
			
			const FVector After = RemoteCharacter->GetActorLocation();

			/*UE_LOG(LogTemp, Display,
				TEXT("[RemoteSnapshotIn] UID=%d Snapshot=(%.1f, %.1f, %.1f) Before=(%.1f, %.1f, %.1f) After=(%.1f, %.1f, %.1f) Anim=%d"),
				Data.userUID,
				Data.x, Data.y, Data.z,
				Before.X, Before.Y, Before.Z,
				After.X, After.Y, After.Z,
				Data.animationNum);*/

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

		Character->PlayAttackMontageFromServer(Packet.AttackType,  Packet.AttackSeq);
		break;
	}
}

void UNetworkInstance::HandleDamageApplied(const FDamageApplyPacket& Packet)
{
	const int32 LocalUID = Client.IsValid() ? Client->ClientPlayerData.userUID : -1;
	const bool bIsLocalTarget = (Packet.TargetID == LocalUID);

	if(AMyCharacter * Character = FindCharacterByUID(Packet.TargetID))
	{
		Character->SetHPFromNetwork(Packet.RemainHP);

		if (Packet.RemainHP <= 0)
		{
			Character->SetStateFromNetwork(1); // Dead
		}

		UE_LOG(LogTemp, Display,
			TEXT("[DamageApplied] Target=%d Damage=%d RemainHP=%d Character=%s"),
			Packet.TargetID,
			Packet.Damage,
			Packet.RemainHP,
			*GetNameSafe(Character));
	}
}

void UNetworkInstance::HandleItemOwnershipChanged(const FItemPacket& Packet)
{
	ABaseItem* Item = FindItemByID(Packet.ItemID);
	if (!Item) { return; }

	if (Packet.bEquipped)
	{
		AMyCharacter* OwnerCharacter = FindCharacterByUID(Packet.OwnerUID);
		if (!OwnerCharacter) { return; }

		UE_LOG(LogTemp, Display, TEXT("[Weapon Ani] Equiped"));
		OwnerCharacter->ApplyEquipItemVisual(Item);
	}
	else
	{
		FVector DropLocation(Packet.X, Packet.Y, Packet.Z);

		if (AMyCharacter* OwnerCharacter = Item->GetOwnerCharacter())
		{
			OwnerCharacter->ApplyDropItemVisual(Item, DropLocation);
		}
		else
		{
			Item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Item->SetOwnerCharacter(nullptr);
			Item->SetActorLocation(DropLocation);
			Item->SetActorEnableCollision(true);

			if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Item->GetRootComponent()))
			{
				Prim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				Prim->SetSimulatePhysics(true);
			}
		}
	}
}

void UNetworkInstance::HandleItemSpawned(const FItemPacket& Packet)
{
	if (Packet.ItemID < 0) { return; }

	if (FindItemByID(Packet.ItemID))
	{
		return;
	}

	TSubclassOf<ABaseItem> ItemClass = GetItemClassByKind(Packet.ItemKind);
	if (!ItemClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[ItemSpawn] ItemClass is not set. ItemKind=%d"), Packet.ItemKind);
		return;
	}

	UWorld* World = GetWorld();
	if (!World) { return; }

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABaseItem* NewItem = World->SpawnActor<ABaseItem>(
		ItemClass,
		FVector(Packet.X, Packet.Y, Packet.Z),
		FRotator::ZeroRotator,
		Params
	);

	if (!NewItem) { return; }

	NewItem->SetItemID(Packet.ItemID);
	NewItem->SetOwnerCharacter(nullptr);
	NewItem->SetActorEnableCollision(true);

	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(NewItem->GetRootComponent()))
	{
		Prim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Prim->SetCollisionResponseToAllChannels(ECR_Ignore);
		Prim->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		Prim->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
		Prim->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		Prim->SetGenerateOverlapEvents(true);
		Prim->SetSimulatePhysics(true);
		Prim->SetEnableGravity(true);
	}

	SpawnedItems.Add(Packet.ItemID, NewItem);
}

void UNetworkInstance::HandleStatusUpdated(const FStatusUpdatePacket& Packet)
{
	if (AMyCharacter* Character = FindCharacterByUID(Packet.TargetID))
	{
		Character->SetHPFromNetwork(Packet.CurrentHP);

		UE_LOG(LogTemp, Display,
			TEXT("[ATK_TRACE][6_ClientHPApply] Target=%d CurrentHP=%d Character=%s"),
			Packet.TargetID,
			Packet.CurrentHP,
			*GetNameSafe(Character));
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

void UNetworkInstance::HandleGameTimeSynced(float SyncedGameTime)
{
	if (UWorld* World = GetWorld())
	{
		if (AInGame_GameState* GS = World->GetGameState<AInGame_GameState>())
		{
			GS->ApplyNetworkGameTime(SyncedGameTime);
		}
	}
}

void UNetworkInstance::HandlePhaseChanged(const FPhaseChangePacket& Packet)
{
	if (UWorld* World = GetWorld())
    {
        if (AInGame_GameState* GS = World->GetGameState<AInGame_GameState>())
        {
            GS->ApplyNetworkPhaseState(Packet);
        }
    }

    UE_LOG(LogTemp, Display,
        TEXT("[NetworkPhase] RoundState=%d Phase=%d GameTime=%.2f"),
        Packet.roundState,
        Packet.mapPhase,
        Packet.gameTime);
}

void UNetworkInstance::HandleMapEventTriggered(const FMapEventPacket& Packet)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	// EMapEventType::Floor == 1
	if (Packet.eventType == 1)
	{
		for (TActorIterator<AIceFloorTile> It(World); It; ++It)
		{
			if (AIceFloorTile* Tile = *It)
			{
				Tile->ApplyNetworkPieceState(Packet.objectIndex, Packet.eventState);
			}
		}

		return;
	}

	// EMapEventType::LargeDebris == 3
	if (Packet.eventType != 3)
	{
		return;
	}

	// EMapEventType::IceChillZone == 4
	if (Packet.eventType == 4) {
		// Delete ChillZone
		if (Packet.eventState == 0)
		{
			if (TWeakObjectPtr<AIceChillZone>* Found = SpawnedIceChillZones.Find(Packet.objectIndex))
			{
				if (AIceChillZone* Zone = Found->Get())
				{
					Zone->Destroy();
				}

				SpawnedIceChillZones.Remove(Packet.objectIndex);
			}
		}
	}

	// 서버 GameLogic.cpp 기준:
	// eventState == 1  -> Activate
	if (Packet.eventState != 1)
	{
		return;
	}


	for (TActorIterator<ALargeDebrisController> It(World); It; ++It)
	{
		ALargeDebrisController* Controller = *It;
		if (!Controller)
		{
			continue;
		}

		Controller->ActivateGameplayRuntime();

		if (Packet.objectIndex == 2)
		{
			Controller->TriggerPhase2Debris();

			UE_LOG(LogTemp, Display,
				TEXT("[LargeDebrisEvent] TriggerPhase2Debris"));
		}
		else if (Packet.objectIndex == 3)
		{
			Controller->TriggerPhase3Debris();

			UE_LOG(LogTemp, Display,
				TEXT("[LargeDebrisEvent] TriggerPhase3Debris"));
		}
	}
}

void UNetworkInstance::HandleObjectSpawned(const FSpawnObjectPacket& Packet)
{
	// EMapEventType::SmallDebris == 2
	if (Packet.objectType == 2) {
		if (Packet.objectID < 0)
		{
			return;
		}

		if (!SmallDebrisClass)
		{
			UE_LOG(LogTemp, Error, TEXT("[DebrisSpawn] SmallDebrisClass is not set."));
			return;
		}

		if (TWeakObjectPtr<ASmallDebrisActor>* Found = SpawnedSmallDebris.Find(Packet.objectID))
		{
			if (Found->IsValid())
			{
				return;
			}
		}

		UWorld* World = GetWorld();
		if (!World)
		{
			return;
		}

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ASmallDebrisActor* NewDebris = World->SpawnActor<ASmallDebrisActor>(
			SmallDebrisClass,
			FVector(Packet.x, Packet.y, Packet.z),
			FRotator::ZeroRotator,
			Params
		);

		if (!NewDebris)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("[DebrisSpawn] Failed to spawn small debris. objectID=%d"),
				Packet.objectID);
			return;
		}

		SpawnedSmallDebris.Add(Packet.objectID, NewDebris);

		UE_LOG(LogTemp, Display,
			TEXT("[DebrisSpawn] Spawned small debris. objectID=%d pos=(%.1f, %.1f, %.1f)"),
			Packet.objectID,
			Packet.x, Packet.y, Packet.z);

		return;
	}

	if (Packet.objectType == 4)
	{
		if (Packet.objectID < 0)
		{
			return;
		}

		if (!IceChillZoneClass)
		{
			UE_LOG(LogTemp, Error, TEXT("[IceChillZoneSpawn] IceChillZoneClass is not set."));
			return;
		}

		if (TWeakObjectPtr<AIceChillZone>* Found = SpawnedIceChillZones.Find(Packet.objectID))
		{
			if (Found->IsValid())
			{
				return;
			}
		}

		UWorld* World = GetWorld();
		if (!World)
		{
			return;
		}

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AIceChillZone* NewZone = World->SpawnActor<AIceChillZone>(
			IceChillZoneClass,
			FVector(Packet.x, Packet.y, Packet.z),
			FRotator::ZeroRotator,
			Params
		);

		if (!NewZone)
		{
			return;
		}

		NewZone->bApplyFreezeLocally = false;
		SpawnedIceChillZones.Add(Packet.objectID, NewZone);
		return;
	}

	if (Packet.objectType == 5) {
		if (!BlackHoleClass)
		{
			UE_LOG(LogTemp, Error, TEXT("[BlackHoleSpawn] BlackHoleClass is not set."));
			return;
		}

		if (TWeakObjectPtr<ABlackHoleActor>* Found = SpawnedBlackHoles.Find(Packet.objectID))
		{
			if (Found->IsValid())
			{
				return;
			}
		}

		UWorld* World = GetWorld();
		if (!World) { return; }

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ABlackHoleActor* NewBlackHole = World->SpawnActor<ABlackHoleActor>(
			BlackHoleClass,
			FVector(Packet.x, Packet.y, Packet.z),
			FRotator::ZeroRotator,
			Params
		);

		if (!NewBlackHole) { return; }

		NewBlackHole->ShowBlackHole();

		// Draw BlackHole Range For Debuging
		const FVector SpawnLocation(Packet.x, Packet.y, Packet.z);

		DrawDebugSphere(
			World,
			SpawnLocation,
			300.0f,
			32,
			FColor::Purple,
			true,
			30.0f,
			0,
			10.0f
		);

		DrawDebugString(
			World,
			SpawnLocation + FVector(0.f, 0.f, 400.f),
			FString::Printf(TEXT("BlackHole ID=%d\n%s"), Packet.objectID, *SpawnLocation.ToString()),
			nullptr,
			FColor::Yellow,
			30.0f,
			true
		);

		// 서버가 실제 흡입을 담당하게 할 거면 클라이언트 흡입은 끄는 게 좋음
		//NewBlackHole->DeactivateBlackHole();

		SpawnedBlackHoles.Add(Packet.objectID, NewBlackHole);

		UE_LOG(LogTemp, Warning,
			TEXT("[BlackHoleSpawn] objectID=%d Location=(%.1f, %.1f, %.1f)"),
			Packet.objectID,
			Packet.x, Packet.y, Packet.z);

		return;
	}
}

void UNetworkInstance::HandleStatusEffect(const FStatusEffectPacket& Packet)
{
	AMyCharacter* Character = FindCharacterByUID(Packet.TargetID);
	if (!Character)
	{
		return;
	}

	if (Packet.EffectType == 0)
	{
		if (Packet.Active != 0)
		{
			Character->ApplyFreeze();
		}
		else
		{
			Character->EndFreeze();
		}
	}
}

void UNetworkInstance::MarkPendingGameplayActivation()
{
	bPendingGameplayActivation = true;
}

bool UNetworkInstance::ConsumePendingGameplayActivation()
{
	if (!bPendingGameplayActivation)
	{
		return false;
	}

	bPendingGameplayActivation = false;
	return true;
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

	if (UCharacterMovementComponent* MoveComp = NewCharacter->GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
		MoveComp->DisableMovement();
		MoveComp->SetComponentTickEnabled(false);
	}

	if (UCapsuleComponent* Capsule = NewCharacter->GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Capsule->SetCollisionObjectType(ECC_Pawn);
		Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
		Capsule->SetGenerateOverlapEvents(true);
	}

	NewCharacter->SetNetworkPlayerUID(Data.userUID);
	RemoteCharacters.Add(Data.userUID, NewCharacter);

	return NewCharacter;
}

ABaseItem* UNetworkInstance::FindItemByID(int32 ItemID) const
{
	if (ItemID < 0)
	{
		return nullptr;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return nullptr;
	}

	for (TActorIterator<ABaseItem> It(World); It; ++It)
	{
		ABaseItem* Item = *It;
		if (!Item)
		{
			continue;
		}

		if (Item->GetItemID() == ItemID)
		{
			return Item;
		}
	}

	return nullptr;
}

TSubclassOf<ABaseItem> UNetworkInstance::GetItemClassByKind(int32 ItemKind) const
{
	switch (static_cast<EClientItemKind>(ItemKind))
	{
		case EClientItemKind::Sword:    return SwordItemClass;
		case EClientItemKind::Spear:    return SpearItemClass;
		case EClientItemKind::Hammer:   return HammerItemClass;
		case EClientItemKind::Umbrella: return UmbrellaItemClass;
		case EClientItemKind::Torch:    return TorchItemClass;
		case EClientItemKind::Grenade:  return GrenadeItemClass;
		default:                        return nullptr;
	}
}
