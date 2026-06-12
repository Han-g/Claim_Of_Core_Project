# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**Claim of Core** - Unreal Engine 5.7 멀티플레이어 3인칭 액션 게임의 클라이언트 코드. 역할 기반 캐릭터(Striker, Guardian, Manipulator), 파괴 가능한 환경, 페이즈 기반 맵 메카닉을 특징으로 한다. 서버 코드는 별도 저장소에 있다.

## Build

표준 UE5 C++ 프로젝트. Visual Studio 또는 Unreal Editor에서 빌드한다.
- 단일 모듈: `Claim_Of_Core` (Runtime)
- Build 설정: `Claim_Of_Core.Build.cs`
- 주요 의존성: EnhancedInput, AIModule, StateTreeModule, GameplayStateTreeModule, UMG, Slate, Sockets, Networking, Niagara

## Architecture

### Module Structure

```
Source/Claim_Of_Core/
  Base/          - GameMode, PlayerController, 모듈 초기화
  Sub/           - 캐릭터 시스템 (MyCharacter, HPComponent)
  Networking/    - 커스텀 소켓 기반 네트워킹 (UE Replication이 아닌 별도 프로토콜)
  UI/            - UMG 위젯 (로그인, 로비, 방, 인게임)
  GameState/     - InGame_GameState (라운드/페이즈 동기화)
  Map/           - 환경 시스템 (파괴, 페이즈 전환)
    IceCave/     - 얼음 동굴 맵 (고드름, 바닥 타일, 페이즈 컨트롤러)
    Building/    - 건물 파괴 (대형/소형 잔해, 스포너)
```

### Networking Layer (핵심 시스템)

UE Replication과 별개로 커스텀 소켓 프로토콜을 사용한다:
- **ClientNetworking**: 메인 스레드에서 커맨드 큐잉 및 델리게이트 브로드캐스트
- **FClientNetworkWorker**: FRunnable 워커 스레드가 소켓 I/O 및 패킷 파싱 담당
- **스레드 안전**: MPSC/SPSC 큐로 스레드 간 통신. 모든 델리게이트는 `PumpEvents()`를 통해 게임 스레드에서만 실행
- **패킷 포맷**: 바이너리 헤더(PacketSize, PacketID) + 직렬화된 구조체

**패킷 ID 범위 규약**:
- 0-99: 시스템 정보 (스냅샷, 방 업데이트, 게임 시간)
- 100-119: 로비 (로그인, 등록, 방 관리)
- 120-149: 인게임 동기화 (데미지, 상태, 애니메이션)
- 150-199: 맵 이벤트 (페이즈 변경, 오브젝트 스폰)
- 500-519: 클라이언트 로비 요청
- 520-549: 클라이언트 키 입력 (이동, 점프)
- 550-599: 클라이언트 게임 로직 (공격, 아이템, 오브젝트 히트)

**NetworkInstance** (UGameInstance 서브클래스)가 ClientNetworking 싱글톤을 보유하고 매 프레임 `Tick()`에서 `PumpEvents()`를 호출한다.

### Character System

**역할 타입**: Striker (대시 속도 부스트), Guardian (방어적 슬로우 + 데미지 감소), Manipulator (확장 점프)
- `OnRep_*` 콜백으로 복제 속성 변경 처리 (HP, 역할, 상태, 스킬)
- 사망 시 관전 모드 전환: 3초 딜레이 후 입력 해제, 2초 후 관전 UI 텍스트 숨김
- 저체력 시 포스트 프로세스/비네트 이펙트 (로컬 클라이언트만)
- 아이템 시스템: BaseItem이 역할별 공격 몽타주, 데미지, 넉백, 범위 정의

### UI Flow

LoginWidget -> RobbyWidget (로비) -> RoomWidget (방) -> InGame

위젯 생명주기는 NetworkInstance가 관리하며, 네트워크 델리게이트로 화면 전환이 트리거된다.

### Map Phase System

- **InGame_GameState**: RoundState (Waiting -> Playing -> Finished), CurrentPhase (None -> Phase1 -> Phase2 -> Phase3 -> End)
- **MapPhaseManager**: 매 틱마다 GameState를 폴링, `OnMapPhaseChanged`/`OnRoundStateChanged` 델리게이트 브로드캐스트
- **페이즈 인식 스폰**: DebrisSpawner와 LargeDebrisController가 CurrentPhase에 따라 스폰 빈도/개수를 조절
- **PreFracturedActor**: 청크 기반 파괴. 인접 그래프 자동 생성, 앵커 시스템, 연쇄 파괴(원래 데미지의 30%)

## Key Conventions

- **서버 권위**: GameState, 데미지, 상태 변경은 서버 권위. 클라이언트는 입력 패킷만 전송
- **이동 동기화**: 커스텀 MovePacket 사용 (UE Replication이 아님) - 클라이언트 예측 없음
- **한국어 주석**: 일부 UI/아이템 코드에 한국어 주석 존재
- **Include 경로**: Build.cs에서 명시적으로 서브디렉토리를 PublicIncludePaths에 등록 (Variant_Platforming, Variant_Combat, Variant_SideScrolling 경로 포함되나 현재 코드에는 해당 폴더 없음 - 향후 확장 예정으로 보임)

## Debugging Tips

- 패킷 흐름: `FClientNetworkWorker::RecvAndParsePackets()`에 로그 추가
- 페이즈 전환: `MapPhaseManager::UpdateFromGameState()`
- HP 복제: `AMyCharacter::OnRep_CurrentHP()`
- 청크 파괴: `ABreakableActor::ApplyBreakableDamage()`
