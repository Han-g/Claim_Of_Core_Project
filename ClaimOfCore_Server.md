Server Client FlowChart

=======================================================



목차

&nbsp; 1. 서버 부트스트랩 (server start-up)

&nbsp; 2. 클라이언트 접속 (TCP accept)

&nbsp; 3. 패킷 수신 → 디스패치

&nbsp; 4. 패킷 송신

&nbsp; 5. 로그인 / 회원가입 (DB 비동기)

&nbsp; 6. 방 생성 / 입장 / 퇴장

&nbsp; 7. 캐릭터 선택 / Ready / 게임 시작

&nbsp; 8. 게임 프레임 루프 (60FPS, 메인 스레드)

&nbsp; 9. 인게임 입력 → 데미지 / 아이템

&nbsp;10. 클라이언트 측 핵심 루프 (Unreal)

&nbsp;11. 흐름 요약





-------------------------------------------------------

1\. 서버 부트스트랩 (server start-up)

-------------------------------------------------------

main()                                           (main.cpp:18)

&nbsp;└─ IOCPServer::InitLogger()                     // logging::configure + CleanupOldLogs

&nbsp;└─ IOCPServer::Init(port=9000, max=3000)

&nbsp;    ├─ WSAStartup

&nbsp;    ├─ CreateIoCompletionPort                   // m\_hIOCP

&nbsp;    ├─ WSASocket / bind / listen                // m\_ListenSocket

&nbsp;    ├─ SessionManager::Init()

&nbsp;    └─ RoomManager::InitManager(this)

&nbsp;└─ IOCPServer::Start()

&nbsp;    ├─ WorkerThread × (CPU\*2)                   // IOCP 완료 처리

&nbsp;    ├─ AcceptThread × 1                         // accept 루프

&nbsp;    └─ DBWorkerThread × 1                       // DB 큐 컨슈머 (DBHelper::Connect 먼저)

&nbsp;└─ while(true): GameFrameProtocol(dt)           // ~16ms 주기 (60FPS)

&nbsp;    └─ RoomManager::UpdateRooms(dt)





-------------------------------------------------------

2\. 클라이언트 접속 (TCP accept → 세션 발급)

-------------------------------------------------------

AcceptThread loop                                (server.cpp:137)

&nbsp;└─ accept(m\_ListenSocket)

&nbsp;└─ SessionManager::AcceptNewClient(socket)      // 빈 슬롯 할당

&nbsp;    └─ (실패 시) closesocket                    // "Session is full"

&nbsp;└─ IOCPServer::OnConnect(newSession, addr)

&nbsp;    ├─ CreateIoCompletionPort(socket → m\_hIOCP)

&nbsp;    ├─ SendPacket(PKT\_S2C\_ACCESS\_ALLOW)         // 첫 핸드셰이크

&nbsp;    └─ WSARecv(첫 비동기 수신 등록)





-------------------------------------------------------

3\. 패킷 수신 → 디스패치 (워커 스레드)

-------------------------------------------------------

WorkerThread loop                                (server.cpp:159)

&nbsp;└─ GetQueuedCompletionStatus

&nbsp;    ├─ 실패 / 0바이트 → OnDisconnect

&nbsp;    └─ p\_Ex->type 분기:

&nbsp;        ├─ RECV → OnRecv(sid, bytes)

&nbsp;        │    ├─ RingBufPush(TempBuffer)

&nbsp;        │    ├─ while: RingBufPeek(header) → RingBufPeek(payload) → RingBufpop

&nbsp;        │    │    └─ PacketProcess(sid, packetID, data)

&nbsp;        │    │         └─ PacketProcessor::Process()

&nbsp;        │    │              └─ m\_FuncHandlerMap\[id](server, session, reader)

&nbsp;        │    └─ WSARecv(다음 수신 재등록)

&nbsp;        ├─ SEND → OnSend(sid, bytes)

&nbsp;        │    ├─ session->sendQueue.pop()

&nbsp;        │    └─ 큐에 더 있으면 SendProtocol() 재호출

&nbsp;        └─ AWAIT → (예약, 미사용)





-------------------------------------------------------

4\. 패킷 송신 (다른 스레드 → IOCP)

-------------------------------------------------------

SendPacket(sid, pid, data, len)                  (server.cpp:328)

&nbsp;├─ PacketHeader 작성 + memcpy → sendQueue.push()

&nbsp;└─ if (!isSending) SendProtocol(session)

&nbsp;    └─ WSASend(sendOverlapped, type=SEND)

&nbsp;        └─ 완료 시 → WorkerThread → OnSend





-------------------------------------------------------

5\. 로그인 / 회원가입 (DB 비동기)

-------------------------------------------------------

\[Recv path]

PacketProcessor::Handle\_LoginReq                 (PacketProcessor.cpp:69)

&nbsp;├─ reader.ReadString(ID / PW)

&nbsp;└─ server->PushDBTask({sid, ID, PW, LOGIN})

&nbsp;    └─ m\_DBLoginQueue.push + condvar.notify\_one



\[DBWorkerThread]

DBWorkerThread loop                              (server.cpp:406)

&nbsp;└─ wait until queue not empty

&nbsp;└─ switch (TaskType):

&nbsp;    ├─ LOGIN → DBHelper::CheckLogin

&nbsp;    │    ├─ 성공: 세션에 playerUID / 이름 캐싱

&nbsp;    │    │    ├─ SessionManager::SetState(LOBBY)

&nbsp;    │    │    ├─ SendPacket(PKT\_S2C\_LOGIN\_OK)

&nbsp;    │    │    └─ BroadcastRoomList()

&nbsp;    │    └─ 실패: SendPacket(PKT\_S2C\_LOGIN\_DENY)

&nbsp;    └─ REGISTER → DBHelper::CreateAccount

&nbsp;         ├─ 성공: SendPacket(PKT\_S2C\_REGISTER\_OK)

&nbsp;         └─ 실패: SendPacket(PKT\_S2C\_REGISTER\_DENY)





-------------------------------------------------------

6\. 방 생성 / 입장 / 퇴장

-------------------------------------------------------

Handle\_Room\_CreateReq

&nbsp;└─ IOCPServer::CreateRoomTry → RoomManager::CreateRoom

&nbsp;    ├─ assignRoomID

&nbsp;    ├─ new Room → Room::InitRoom(id, this)

&nbsp;    └─ JoinRoom(client, newID)                  // 작성자 자동 입장



Handle\_Room\_JoinReq

&nbsp;└─ JoinRoomTry → RoomManager::JoinRoom

&nbsp;    ├─ Room::addMember

&nbsp;    │    ├─ AllocateRoomSlot

&nbsp;    │    └─ TeamCalculateBySlot

&nbsp;    ├─ SessionManager::SetState(ROOM)

&nbsp;    ├─ Room::GetMemberInfoList

&nbsp;    ├─ SendPacket(PKT\_S2C\_ROOM\_ENTER)           → 본인

&nbsp;    ├─ Room::BroadcastToMembers(PKT\_S2C\_ROOM\_INFO\_BRD)  → 기존 멤버

&nbsp;    └─ BroadcastRoomList()



OnDisconnect / LeaveRoom

&nbsp;└─ RoomManager::LeaveRoom (or LeaveRoomByDisconnect)

&nbsp;    ├─ Room::RemoveMember

&nbsp;    ├─ IsEmpty       → DestroyRoom

&nbsp;    ├─ wasOwner      → Room::TransferOwnership

&nbsp;    ├─ Room::BroadcastToMembers(ROOM\_INFO\_BRD)

&nbsp;    └─ BroadcastRoomList





-------------------------------------------------------

7\. 캐릭터 선택 / Ready / 게임 시작

-------------------------------------------------------

Handle\_Character\_SelectReq

&nbsp;├─ session->gameDatas.roleType = roleType

&nbsp;└─ Room::BroadcastToMembers(PKT\_S2C\_CHARACTER\_SELECT\_BRD)



Handle\_Game\_ReadyReq

&nbsp;├─ session->isReady ^= 1

&nbsp;└─ IOCPServer::BroadcastRoomInfo → ROOM\_INFO\_BRD



Handle\_Game\_StartReq

&nbsp;└─ GameStartTry → RoomManager::GameStart

&nbsp;    ├─ IsOwner 검증           → 실패: PKT\_S2C\_ERROR(5)

&nbsp;    ├─ Room::IsAllReady       → 실패: PKT\_S2C\_ERROR(4)

&nbsp;    ├─ Room::SetState(PLAYING)

&nbsp;    ├─ 무작위 맵 추첨 → SelectStage / LoadStage

&nbsp;    ├─ BroadcastToMembers(PKT\_S2C\_MAP\_SELECT\_NOTICE)

&nbsp;    ├─ new GameLogic → Room::InitGameLogic(logic)

&nbsp;    │    └─ for member: InitCharacter

&nbsp;    │         ├─ TeamCalculateBySlot

&nbsp;    │         ├─ ApplyRoleStats (HP / 속도)

&nbsp;    │         └─ GetRespawnLocation / GetSpawnYawBySlot

&nbsp;    ├─ BroadcastToMembers(PKT\_S2C\_GAME\_START\_BRD)

&nbsp;    └─ Room::BeginDeferredRoundStart(3.0f)





-------------------------------------------------------

8\. 게임 프레임 루프 (60FPS, 메인 스레드)

-------------------------------------------------------

main loop (16ms)

&nbsp;└─ IOCPServer::GameFrameProtocol(dt)

&nbsp;    └─ RoomManager::UpdateRooms(dt)

&nbsp;        for each room:

&nbsp;         ├─ Room::UpdateGameLogic(dt)

&nbsp;         │    ├─ bPendingRoundStart 카운트다운 → GameLogic::StartGameRound

&nbsp;         │    │    ├─ phase 타이머 초기화

&nbsp;         │    │    ├─ 맵별 부트스트랩 (StartIceMap 등)

&nbsp;         │    │    └─ BroadcastToMembers(PHASE\_CHANGE\_BRD : phase1)

&nbsp;         │    └─ GameLogic::Update(dt)

&nbsp;         │         ├─ timeAccumlator += dt

&nbsp;         │         ├─ while ≥ 1초 : CountdownTick

&nbsp;         │         │    ├─ BroadcastGameTime

&nbsp;         │         │    ├─ phase 임계 통과 → HandlePhaseChanged

&nbsp;         │         │    └─ time ≤ 0 → EndGameRound (PHASE\_CHANGE : Finished)

&nbsp;         │         ├─ for player : UpdatePlayerMovement

&nbsp;         │         │    ├─ GetRoleSpeedMultiplier

&nbsp;         │         │    └─ ResolveMovementWithCollision

&nbsp;         │         └─ mapType 분기 :

&nbsp;         │              ├─ 1 : UpdateBuildingMap

&nbsp;         │              │     └─ UpdateDebrisSpawner → SpawnDebrisByPhase

&nbsp;         │              │           └─ SpawnSmallDebris (broadcast)

&nbsp;         │              └─ 2 : UpdateIceCaveMap

&nbsp;         │                    ├─ TriggerRandomIcicle → StartIcicleWarning

&nbsp;         │                    │       → StartIcicleFalling → BreakIcicle

&nbsp;         │                    └─ TriggerRandomFloorTile → SetFloorCracked

&nbsp;         │                            → StartFloorBreaking → BreakFloor

&nbsp;         └─ Room::BroadcastGameDatas

&nbsp;             └─ SendPacket(PKT\_S2C\_SNAPSHOT\_NOTICE) → 멤버 전원





-------------------------------------------------------

9\. 인게임 입력 → 데미지 / 아이템 처리

-------------------------------------------------------

\[Move]

Handle\_Move\_KeyInput

&nbsp;├─ reader.Read(MovePacket)

&nbsp;├─ velocity clamp / NaN 보정

&nbsp;└─ session->LastMoveIntent 갱신                 (실제 위치는 다음 Update에서 적용)



\[Attack]

Handle\_Attack\_KeyInput

&nbsp;└─ PacketProcessor::GameLogicHelper(server, session)

&nbsp;    └─ Room이 PLAYING 일 때만 logic 반환

&nbsp;└─ GameLogic::HandleAttackInput

&nbsp;    ├─ GetAttackMontageByRole

&nbsp;    ├─ DoHit                                    (사거리 · 반경 검사)

&nbsp;    ├─ ApplyDamageToTarget → ApplyDamage

&nbsp;    │    ├─ SetCurrentHP

&nbsp;    │    ├─ BroadcastDamageApply

&nbsp;    │    └─ HP 0 → HandleDeath

&nbsp;    │         ├─ SetCharacterState(Dead) → BroadcastStateChange

&nbsp;    │         └─ (RespawnTime 후) HandleRespawn

&nbsp;    │              ├─ ResetHP

&nbsp;    │              ├─ GetRespawnLocation

&nbsp;    │              └─ BroadcastRespawn

&nbsp;    └─ ApplyKnockback / BroadcastAttackAction



\[Item]

Handle\_ItemPickup\_KeyInput → GameLogic::HandleItemPickup

&nbsp;    └─ Room::GetItemData → ownerUID 갱신 → broadcast(ITEM\_\*)

Handle\_ItemDrop\_KeyInput   → GameLogic::DropCurrentItem





-------------------------------------------------------

10\. 클라이언트 측 핵심 루프 (Unreal)

-------------------------------------------------------

UNetworkInstance::Init                           (NetworkInstance.cpp)

&nbsp;├─ ShowLoginHUD                                 (위젯 생성)

&nbsp;└─ Client = MakeShared<ClientNetworking>

&nbsp;    └─ ClientNetworking::Start(IP, Port)

&nbsp;        ├─ Worker = MakeShared<FClientNetworkWorker>

&nbsp;        └─ RequestConnect → InboundCommandQueue.Enqueue → Worker::WakeUp



FClientNetworkWorker::Run        (워커 스레드)   (ClientNetworkWorker)

&nbsp;loop:

&nbsp; ├─ FlushInboundCommands                        // CONNECT / DISCONNECT / SEND 처리

&nbsp; │    ├─ CONNECT → TryConnectBlocking

&nbsp; │    └─ SEND    → SendRawPacket                (헤더 + payload)

&nbsp; ├─ RecvAndParsePackets

&nbsp; │    ├─ Socket->Recv → RecvBuffer 누적

&nbsp; │    └─ while 헤더 + 바디 완성:

&nbsp; │         └─ HandlePacket(header, payload, size)

&nbsp; │              └─ PushEvent({타입, 데이터}) → OutboundEventQueue

&nbsp; └─ HandleReconnect                             (필요 시)



UNetworkInstance::Tick           (게임 스레드, 매 프레임)

&nbsp;└─ Client->PumpEvents

&nbsp;    └─ OutboundEventQueue 드레인:

&nbsp;        ├─ Connected / Disconnected → HandleConnected / HandleDisconnected

&nbsp;        ├─ LoginResult              → HandleLoginResult       → 위젯 전환

&nbsp;        ├─ RoomListUpdated          → HandleRoomListUpdate    → 로비 갱신

&nbsp;        ├─ RoomEntered              → HandleRoomEnterResult   → RoomWidget

&nbsp;        ├─ MapSelected              → HandleMapSelected

&nbsp;        ├─ GameStart                → HandleGameStart         → MarkPendingGameplayActivation

&nbsp;        ├─ Snapshot                 → HandleSnapshotReceived

&nbsp;        │                             ├─ FindCharacterByUID

&nbsp;        │                             └─ EnsureRemoteCharacter (없으면 스폰)

&nbsp;        ├─ AttackAction             → HandleAttackActionReceived (몽타주 재생)

&nbsp;        ├─ DamageApplied            → HandleDamageApplied     (HP UI / FX)

&nbsp;        ├─ StatusUpdated            → HandleStatusUpdated

&nbsp;        ├─ StateChanged             → HandleStateChanged      (사망 / 관전)

&nbsp;        ├─ Respawned                → HandleRespawned

&nbsp;        ├─ GameTimeSynced           → HandleGameTimeSynced

&nbsp;        ├─ PhaseChanged             → HandlePhaseChanged      → MapPhaseManager

&nbsp;        ├─ MapEventTriggered        → HandleMapEventTriggered

&nbsp;        ├─ ObjectSpawned            → HandleObjectSpawned     (debris 스폰)

&nbsp;        └─ ItemOwnership            → HandleItemOwnershipChanged



\[클라 → 서버 입력 송출]

&nbsp;Login UI            → TryLogin               → ClientNetworking::LoginAccess

&nbsp;RoomList click      → JoinRoom               → JoinRoomRequest

&nbsp;역할 선택           → SelectCharacterAndReady → CharacterSelectRequest + ReadyToggleRequest

&nbsp;방장 시작           → RequestGameStart        → GameStartRequest

&nbsp;플레이어 이동       → MyCharacter Tick        → SendMoveInputToServer → SendMoveInput

&nbsp;공격 키             → RequestAttackInput      → (현재 코드는 공격 패킷 enqueue 없음 — Attack은 서버 핸들러만 정의됨)

&nbsp;아이템 줍기 / 버리기 → RequestItemPickup / Drop → ItemPickupRequest / ItemDropRequest

&nbsp;       └─ (모두 EnqueueSendCommand → 워커가 SendRawPacket)





-------------------------------------------------------

11\. 흐름 요약 (한 줄로)

-------------------------------------------------------

&nbsp;· 접속

&nbsp;    진입 : AcceptThread → OnConnect

&nbsp;    종착 : PKT\_S2C\_ACCESS\_ALLOW



&nbsp;· 로그인

&nbsp;    진입 : Handle\_LoginReq → DBWorkerThread::CheckLogin

&nbsp;    종착 : PKT\_S2C\_LOGIN\_OK + BroadcastRoomList



&nbsp;· 방 생성 / 입장

&nbsp;    진입 : RoomManager::CreateRoom / JoinRoom

&nbsp;    종착 : ROOM\_ENTER + ROOM\_INFO\_BRD + ROOM\_UPDATE



&nbsp;· 캐릭터 선택

&nbsp;    진입 : Handle\_Character\_SelectReq

&nbsp;    종착 : CHARACTER\_SELECT\_BRD



&nbsp;· Ready

&nbsp;    진입 : Handle\_Game\_ReadyReq

&nbsp;    종착 : ROOM\_INFO\_BRD



&nbsp;· 게임 시작

&nbsp;    진입 : RoomManager::GameStart → Room::InitGameLogic

&nbsp;    종착 : MAP\_SELECT\_NOTICE + GAME\_START\_BRD → 3초 후 PHASE\_CHANGE\_BRD



&nbsp;· 매 프레임

&nbsp;    진입 : GameFrameProtocol → Room::UpdateGameLogic + BroadcastGameDatas

&nbsp;    종착 : SNAPSHOT\_NOTICE



&nbsp;· 카운트다운 / 페이즈

&nbsp;    진입 : GameLogic::CountdownTick → HandlePhaseChanged

&nbsp;    종착 : SYNC\_GAME\_TIME + PHASE\_CHANGE\_BRD



&nbsp;· 이동

&nbsp;    진입 : Handle\_Move\_KeyInput → LastMoveIntent

&nbsp;    종착 : (다음 Update에서 위치 적용 후 SNAPSHOT)



&nbsp;· 공격

&nbsp;    진입 : Handle\_Attack\_KeyInput → GameLogic::HandleAttackInput → ApplyDamage

&nbsp;    종착 : DAMAGE\_APPLY\_BRD (+사망 시 STATE / RESPAWN\_BRD)



&nbsp;· 맵 위험요소 (Building)

&nbsp;    진입 : UpdateDebrisSpawner → SpawnSmallDebris

&nbsp;    종착 : MAP\_EVENT\_\* / SPAWN\_OBJECT



&nbsp;· 맵 위험요소 (IceCave)

&nbsp;    진입 : TriggerRandomIcicle / TriggerRandomFloorTile

&nbsp;    종착 : MAP\_EVENT\_\*





