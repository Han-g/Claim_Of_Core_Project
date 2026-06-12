# -*- coding: utf-8 -*-
"""
Claim of Core 프로젝트 - 코드 문서 PDF 생성 스크립트
- Client (Unreal C++) + Server (Win32 IOCP C++) 의 함수/변수를 파일별로 정리
- 한글 폰트: Windows Malgun Gothic
"""

from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import mm
from reportlab.lib import colors
from reportlab.lib.enums import TA_LEFT
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, PageBreak,
    Table, TableStyle, KeepTogether
)

# ----- Font Setup -----
pdfmetrics.registerFont(TTFont('Malgun', 'C:/Windows/Fonts/malgun.ttf'))
pdfmetrics.registerFont(TTFont('MalgunBd', 'C:/Windows/Fonts/malgunbd.ttf'))

# ----- Styles -----
base = getSampleStyleSheet()

style_title = ParagraphStyle('Title', parent=base['Title'],
                             fontName='MalgunBd', fontSize=22, leading=28,
                             alignment=1, spaceAfter=12)
style_h1 = ParagraphStyle('H1', parent=base['Heading1'],
                          fontName='MalgunBd', fontSize=18, leading=22,
                          textColor=colors.HexColor('#1F3864'),
                          spaceBefore=12, spaceAfter=8)
style_h2 = ParagraphStyle('H2', parent=base['Heading2'],
                          fontName='MalgunBd', fontSize=14, leading=18,
                          textColor=colors.HexColor('#2E75B6'),
                          spaceBefore=10, spaceAfter=6)
style_h3 = ParagraphStyle('H3', parent=base['Heading3'],
                          fontName='MalgunBd', fontSize=11, leading=14,
                          textColor=colors.HexColor('#264478'),
                          spaceBefore=6, spaceAfter=3)
style_body = ParagraphStyle('Body', parent=base['BodyText'],
                            fontName='Malgun', fontSize=9, leading=12,
                            alignment=TA_LEFT, spaceAfter=4)
style_code = ParagraphStyle('Code', parent=base['BodyText'],
                            fontName='Courier', fontSize=8, leading=10,
                            backColor=colors.HexColor('#F2F2F2'),
                            borderColor=colors.HexColor('#CCCCCC'),
                            borderWidth=0.5, borderPadding=3,
                            spaceAfter=4)
style_note = ParagraphStyle('Note', parent=base['BodyText'],
                            fontName='Malgun', fontSize=8, leading=11,
                            textColor=colors.HexColor('#555555'),
                            alignment=TA_LEFT, spaceAfter=4)


def P(text, style=style_body):
    """짧은 헬퍼"""
    return Paragraph(text, style)


def file_section(file_path, summary, items):
    """
    items: list of dicts
       {'kind': 'class'|'function'|'variable'|'enum', 'sig': ..., 'desc': ...}
    """
    flow = []
    flow.append(P(file_path, style_h2))
    flow.append(P(summary, style_body))
    flow.append(Spacer(1, 2 * mm))

    rows = [['종류', '시그니처 / 이름', '설명']]
    for it in items:
        rows.append([
            it['kind'],
            Paragraph(it['sig'], ParagraphStyle('cell_sig', fontName='Courier', fontSize=7.5, leading=10)),
            Paragraph(it['desc'], ParagraphStyle('cell_desc', fontName='Malgun', fontSize=8, leading=10)),
        ])

    tbl = Table(rows, colWidths=[18 * mm, 70 * mm, 92 * mm], repeatRows=1)
    tbl.setStyle(TableStyle([
        ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor('#1F3864')),
        ('TEXTCOLOR', (0, 0), (-1, 0), colors.white),
        ('FONTNAME', (0, 0), (-1, 0), 'MalgunBd'),
        ('FONTSIZE', (0, 0), (-1, 0), 9),
        ('ALIGN', (0, 0), (-1, 0), 'CENTER'),
        ('GRID', (0, 0), (-1, -1), 0.4, colors.HexColor('#888888')),
        ('VALIGN', (0, 0), (-1, -1), 'TOP'),
        ('LEFTPADDING', (0, 0), (-1, -1), 4),
        ('RIGHTPADDING', (0, 0), (-1, -1), 4),
        ('TOPPADDING', (0, 0), (-1, -1), 3),
        ('BOTTOMPADDING', (0, 0), (-1, -1), 3),
        ('FONTNAME', (0, 1), (0, -1), 'Malgun'),
        ('FONTSIZE', (0, 1), (0, -1), 8),
        ('ALIGN', (0, 1), (0, -1), 'CENTER'),
        ('ROWBACKGROUNDS', (0, 1), (-1, -1), [colors.white, colors.HexColor('#F7F7F7')]),
    ]))
    flow.append(tbl)
    flow.append(Spacer(1, 6 * mm))
    return flow


# ============================================================
# 클라이언트 파일 데이터
# ============================================================

CLIENT_FILES = [
    # ---------------- Base ----------------
    {
        'path': 'Base/Claim_Of_Core.h / .cpp',
        'summary': 'Unreal 모듈 진입점. 로그 카테고리 LogClaim_Of_Core 를 선언하고, IMPLEMENT_PRIMARY_GAME_MODULE 매크로로 모듈을 등록한다.',
        'items': [
            {'kind': '매크로', 'sig': 'DECLARE_LOG_CATEGORY_EXTERN(LogClaim_Of_Core, Log, All)',
             'desc': '프로젝트 전반에서 UE_LOG 호출에 사용할 로그 카테고리를 선언한다.'},
            {'kind': '매크로', 'sig': 'IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Claim_Of_Core, "Claim_Of_Core")',
             'desc': '메인 게임 모듈로서 엔진에 등록한다.'},
        ],
    },
    {
        'path': 'Base/Claim_Of_CorePlayerController.h / .cpp',
        'summary': 'APlayerController 파생 클래스. EnhancedInput용 InputMappingContext, 모바일 터치 컨트롤 토글, 가상 조이스틱 위젯 클래스를 보유한다.',
        'items': [
            {'kind': 'class', 'sig': 'AClaim_Of_CorePlayerController : public APlayerController',
             'desc': '플레이어 입력/카메라/UI 컨트롤을 담당하는 컨트롤러.'},
            {'kind': 'function', 'sig': 'virtual void BeginPlay() override',
             'desc': '플랫폼에 따라 모바일/데스크톱 입력 컨텍스트를 등록하고 가상 조이스틱을 표시한다.'},
            {'kind': 'function', 'sig': 'virtual void SetupInputComponent() override',
             'desc': 'EnhancedInput 액션 바인딩을 구성한다.'},
            {'kind': 'variable', 'sig': 'TArray<UInputMappingContext*> DefaultMappingContexts',
             'desc': '데스크톱 환경에서 사용할 기본 매핑 컨텍스트 목록.'},
            {'kind': 'variable', 'sig': 'TArray<UInputMappingContext*> MobileMappingContexts',
             'desc': '모바일 환경 전용 매핑 컨텍스트 목록.'},
            {'kind': 'variable', 'sig': 'TSubclassOf<UUserWidget> MobileControlsWidgetClass',
             'desc': '모바일에서 표시할 가상 조이스틱 위젯의 클래스.'},
            {'kind': 'variable', 'sig': 'TObjectPtr<UUserWidget> MobileControlsWidget',
             'desc': '런타임에 생성된 가상 조이스틱 위젯 인스턴스.'},
        ],
    },

    # ---------------- Sub (캐릭터) ----------------
    {
        'path': 'Sub/MyCharacter.h',
        'summary': '게임의 메인 캐릭터 클래스. 서버 권위 동기화(MovePacket·Snapshot 기반), 역할(Striker/Guardian/Manipulator) 시스템, 사망/관전 처리, 저체력 효과 등을 담당.',
        'items': [
            {'kind': 'class', 'sig': 'AMyCharacter : public ACharacter',
             'desc': '커스텀 네트워크 프로토콜로 동기화되는 3인칭 캐릭터.'},
            {'kind': 'function', 'sig': 'virtual void BeginPlay() override',
             'desc': '카메라/스프링암 초기 설정과 위젯·델리게이트 바인딩을 수행한다.'},
            {'kind': 'function', 'sig': 'virtual void Tick(float DeltaSeconds) override',
             'desc': '20fps 주기로 FMovePacket을 서버로 전송하고, 사망 카메라/저체력 효과를 갱신한다.'},
            {'kind': 'function', 'sig': 'virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override',
             'desc': 'MaxHP, CurrentHP, CharacterState, RoleType, bRoleSkillActive를 복제 등록한다.'},
            {'kind': 'function', 'sig': 'void Move(const FInputActionValue& Value)',
             'desc': '이동 입력을 처리한다(서버 전송용 입력 누적).'},
            {'kind': 'function', 'sig': 'void Look(const FInputActionValue& Value)',
             'desc': '카메라 회전(피치/요)을 처리한다.'},
            {'kind': 'function', 'sig': 'void DoJumpStart() / DoJumpEnd()',
             'desc': '점프 시작/종료를 처리한다.'},
            {'kind': 'function', 'sig': 'void OnRep_CurrentHP()',
             'desc': '현재 HP 복제 콜백. HP 텍스트 갱신과 저체력 비네트/포스트프로세스 효과 반영.'},
            {'kind': 'function', 'sig': 'void OnRep_RoleType()',
             'desc': '역할 변경 시 이동 속도/메시/스킬 파라미터를 재적용한다.'},
            {'kind': 'function', 'sig': 'void OnRep_CharacterState()',
             'desc': '생존/사망 상태 변경에 따라 입력 잠금, 관전 카메라 진입을 수행한다.'},
            {'kind': 'function', 'sig': 'void OnRep_RoleSkillActive()',
             'desc': '역할 스킬 활성/비활성에 따른 비주얼/스탯 토글.'},
            {'kind': 'function', 'sig': 'void ActivateRoleSkill() (Server RPC)',
             'desc': '역할별 고유 스킬을 발동한다(Striker 대시·Guardian 슬로우·Manipulator 점프 강화).'},
            {'kind': 'function', 'sig': 'void DeactivateRoleSkill()',
             'desc': '스킬 타이머 종료 시 호출되어 효과를 원복한다.'},
            {'kind': 'function', 'sig': 'void SetRoleFromNetwork(int32) / SetHPFromNetwork(int32, int32) / SetStateFromNetwork(int32)',
             'desc': '서버 스냅샷에서 받은 값을 캐릭터 상태에 반영한다.'},
            {'kind': 'function', 'sig': 'void ApplyTransformFromNetwork(const FVector&, float Yaw)',
             'desc': '서버가 보낸 위치/요로 트랜스폼을 보정한다(원격 캐릭터에 사용).'},
            {'kind': 'function', 'sig': 'void EnterSpectateMode() / ExitSpectateMode()',
             'desc': '사망 후 자유 시점 관전 모드 진입/종료.'},
            {'kind': 'variable', 'sig': 'USpringArmComponent* SpringArm / UCameraComponent* Camera',
             'desc': '3인칭 카메라 구성요소.'},
            {'kind': 'variable', 'sig': 'int32 MaxHP, CurrentHP (ReplicatedUsing)',
             'desc': '서버 권위 HP. OnRep_* 콜백으로 UI/효과 갱신.'},
            {'kind': 'variable', 'sig': 'uint8 CharacterState (ReplicatedUsing)',
             'desc': '0=생존 / 1=사망. 사망 시 입력/물리/UI 전환 트리거.'},
            {'kind': 'variable', 'sig': 'uint8 RoleType (ReplicatedUsing)',
             'desc': '0=Striker, 1=Guardian, 2=Manipulator.'},
            {'kind': 'variable', 'sig': 'bool bRoleSkillActive (ReplicatedUsing)',
             'desc': '스킬 활성 여부. 시각/스탯 토글에 사용.'},
            {'kind': 'variable', 'sig': 'float DashDuration=5, DashSpeedMult=1.45',
             'desc': 'Striker 대시 스킬의 지속 시간/속도 배수.'},
            {'kind': 'variable', 'sig': 'float HardDuration=5, HardScaleMult=1.25',
             'desc': 'Guardian 방어 스킬 지속 시간/스케일 배수.'},
            {'kind': 'variable', 'sig': 'float DBJPDuration=10',
             'desc': 'Manipulator 점프 강화 스킬 지속 시간.'},
            {'kind': 'variable', 'sig': 'float SpectateMoveSpeed=900',
             'desc': '관전 모드의 자유 이동 속도.'},
        ],
    },
    {
        'path': 'Sub/HPComponent.h / .cpp',
        'summary': '체력을 캡슐화한 ActorComponent. 데미지·회복·리셋 호출 시 OnHPChanged / OnHPZero 델리게이트를 브로드캐스트한다. Server RPC 변형이 함께 제공된다.',
        'items': [
            {'kind': 'class', 'sig': 'UHPComponent : public UActorComponent',
             'desc': 'HP를 별도 컴포넌트로 분리해 캐릭터/오브젝트에 부착.'},
            {'kind': 'function', 'sig': 'void ApplyDamage(int32 Amount) / Server RPC 변형',
             'desc': 'HP에서 Amount 만큼 차감 후 델리게이트를 호출. 0 이하가 되면 OnHPZero 발동.'},
            {'kind': 'function', 'sig': 'void Heal(int32 Amount) / Server RPC 변형',
             'desc': 'HP를 회복한다(MaxHP 클램프).'},
            {'kind': 'function', 'sig': 'void ResetHP() / Server RPC 변형',
             'desc': 'HP를 MaxHP로 초기화한다.'},
            {'kind': 'delegate', 'sig': 'OnHPChanged(int32 Cur, int32 Max)',
             'desc': 'HP 변경 시 외부에 통지.'},
            {'kind': 'delegate', 'sig': 'OnHPZero()',
             'desc': '사망(또는 파괴) 트리거.'},
            {'kind': 'variable', 'sig': 'int32 MaxHP / CurrentHP',
             'desc': '체력 범위. UPROPERTY Replicated.'},
        ],
    },
    {
        'path': 'Sub/BaseItem.h / .cpp',
        'summary': '플레이어가 줍거나 장착하는 무기/도구 액터의 기반 클래스. 역할별 공격 몽타주, 데미지/넉백/범위/콜리전 처리를 포함한다.',
        'items': [
            {'kind': 'class', 'sig': 'ABaseItem : public AActor',
             'desc': '픽업·장착·공격을 모두 담당하는 베이스 아이템.'},
            {'kind': 'function', 'sig': 'void StartUse(AMyCharacter* User)',
             'desc': '아이템 사용을 개시(역할별 공격 몽타주 실행 등).'},
            {'kind': 'function', 'sig': 'void DoHit(AMyCharacter* User)',
             'desc': '공격 히트 판정. SphereOverlap으로 대상 검색 후 ApplyDamage·ApplyKnockback 실행.'},
            {'kind': 'function', 'sig': 'void ApplyDamage(AActor* Target, AMyCharacter* User)',
             'desc': 'UGameplayStatics::ApplyDamage로 데미지를 가한다.'},
            {'kind': 'function', 'sig': 'void ApplyKnockback(AMyCharacter* Target, const FVector& Dir)',
             'desc': 'LaunchCharacter로 넉백을 적용한다.'},
            {'kind': 'variable', 'sig': 'USphereComponent* PickupCollision',
             'desc': '픽업 트리거용 콜리전.'},
            {'kind': 'variable', 'sig': 'UAnimMontage* Montage_Striker / Guardian / Manipulator',
             'desc': '역할별 공격 애니메이션.'},
            {'kind': 'variable', 'sig': 'float Damage=20.f, KnockbackPower=800.f',
             'desc': '기본 공격 데미지와 넉백 강도.'},
            {'kind': 'variable', 'sig': 'float Range=200.f, Radius=80.f',
             'desc': '공격 범위(전방 거리)와 구체 반경.'},
        ],
    },

    # ---------------- Networking ----------------
    {
        'path': 'Networking/ClientNetworkTypes.h',
        'summary': '클라이언트 네트워크 계층의 공용 타입. 모든 PacketID, 패킷 구조체, FNetCommand·FNetEvent 큐 메시지가 정의된다.',
        'items': [
            {'kind': 'enum', 'sig': 'enum PacketID : uint16',
             'desc': '0~99 시스템, 100~119 로비 S2C, 120~149 인게임 동기화, 150~199 맵 이벤트, 500~599 클라이언트 요청.'},
            {'kind': 'struct', 'sig': 'GameData',
             'desc': 'userUID, x/y/z, rotate, currentHP/maxHP, characterState, roleType, animationNum 등 플레이어 스냅샷.'},
            {'kind': 'struct', 'sig': 'FPacketHeader { uint16 PacketSize; uint16 PacketID; }',
             'desc': '모든 패킷의 공통 헤더.'},
            {'kind': 'struct', 'sig': 'FLoginPacket / FRoomPacketData / FRoomMemberInfo',
             'desc': '로비 단계의 로그인/방 목록/방 멤버 정보.'},
            {'kind': 'struct', 'sig': 'FMovePacket',
             'desc': '클라 → 서버 이동 입력. (x,y,z,yaw,vx,vy)'},
            {'kind': 'struct', 'sig': 'FAttackActionPacket / FDamageApplyPacket / FStatusUpdatePacket',
             'desc': '공격 발동 / 데미지 적용 / HP 갱신 브로드캐스트.'},
            {'kind': 'struct', 'sig': 'FStateChangePacket / FRespawnPacket / FRoleChangePacket',
             'desc': '캐릭터 상태/리스폰/역할 변경 브로드캐스트.'},
            {'kind': 'struct', 'sig': 'FMapEventPacket / FSpawnObjectPacket / FPhaseChangePacket',
             'desc': '맵 이벤트(아이시클·바닥 타일·잔해), 오브젝트 스폰, 페이즈 전환.'},
            {'kind': 'struct', 'sig': 'FSyncGameTimePacket / FSyncAnimationPacket',
             'desc': '게임 타이머/애니메이션 동기화.'},
            {'kind': 'struct', 'sig': 'FNetCommand',
             'desc': '게임 스레드 → 워커 스레드 명령(MPSC 큐).'},
            {'kind': 'struct', 'sig': 'FNetEvent',
             'desc': '워커 스레드 → 게임 스레드 결과(SPSC 큐). PumpEvents에서 소비.'},
        ],
    },
    {
        'path': 'Networking/ClientNetworking.h / .cpp',
        'summary': '메인 스레드용 네트워킹 파사드. 워커 스레드에 명령을 발행하고, PumpEvents로 큐를 비우며 델리게이트를 브로드캐스트한다.',
        'items': [
            {'kind': 'class', 'sig': 'class ClientNetworking',
             'desc': 'NetworkInstance가 보유하는 싱글톤성 파사드.'},
            {'kind': 'function', 'sig': 'void Start(const FString& IP, int32 Port)',
             'desc': '워커 스레드를 생성하고 접속을 시도한다.'},
            {'kind': 'function', 'sig': 'void Shutdown()',
             'desc': '워커 스레드 정지·소켓 해제.'},
            {'kind': 'function', 'sig': 'void PumpEvents()',
             'desc': '아웃바운드 이벤트 큐를 모두 소비해 적절한 델리게이트를 브로드캐스트.'},
            {'kind': 'function', 'sig': 'void LoginAccess(FString ID, FString PW)',
             'desc': 'FBufferArchive로 ID/PW를 직렬화 후 PKT_C2S_LOGIN_REQ 전송.'},
            {'kind': 'function', 'sig': 'void RegisterRequest(FString ID, FString PW)',
             'desc': '계정 생성 요청 패킷.'},
            {'kind': 'function', 'sig': 'void CreateRoomRequest() / JoinRoomRequest(int32) / GameStartRequest()',
             'desc': '방 생성·입장·게임 시작 요청.'},
            {'kind': 'function', 'sig': 'void CharacterSelectRequest(int32 RoleType) / ReadyRequest()',
             'desc': '역할 선택과 레디 토글.'},
            {'kind': 'function', 'sig': 'void SendMovePacket(const FMovePacket&)',
             'desc': '클라이언트 이동 입력 송신(20Hz).'},
            {'kind': 'delegate', 'sig': 'OnLoginResult / OnRegisterResult / OnRoomList / OnRoomEnter / OnGameStart',
             'desc': '로비 단계 결과를 NetworkInstance/위젯에 통지.'},
            {'kind': 'delegate', 'sig': 'OnSnapshot / OnAttackAction / OnDamageApply / OnStatusUpdate / OnStateChange / OnRespawn',
             'desc': '인게임 동기화 이벤트.'},
            {'kind': 'variable', 'sig': 'TUniquePtr<FRunnableThread> WorkerThread / FClientNetworkWorker* Worker',
             'desc': '실제 소켓 I/O를 수행하는 워커 스레드.'},
        ],
    },
    {
        'path': 'Networking/ClientNetworkWorker.h / .cpp',
        'summary': '소켓 I/O와 패킷 파싱 전담 FRunnable 워커. 10ms 간격 루프에서 InboundCommand 처리, 재접속, RecvAndParsePackets를 수행한다.',
        'items': [
            {'kind': 'class', 'sig': 'class FClientNetworkWorker : public FRunnable',
             'desc': '메인 스레드와 분리된 네트워크 워커.'},
            {'kind': 'function', 'sig': 'virtual uint32 Run() override',
             'desc': '메인 루프. FlushInboundCommands → HandleReconnect → RecvAndParsePackets → 10ms 슬립.'},
            {'kind': 'function', 'sig': 'void FlushInboundCommands()',
             'desc': 'Mpsc 큐에 쌓인 FNetCommand를 처리(연결/송신/종료 등).'},
            {'kind': 'function', 'sig': 'void RecvAndParsePackets()',
             'desc': '소켓에서 데이터를 수신해 헤더 길이 프로토콜로 분할 후 HandlePacket 호출.'},
            {'kind': 'function', 'sig': 'void HandlePacket(uint16 PacketID, const TArray<uint8>& Body)',
             'desc': 'PacketID switch 문으로 구조체를 memcpy해 FNetEvent에 적재.'},
            {'kind': 'function', 'sig': 'void HandleReconnect()',
             'desc': '연결 실패 시 ReconnectIntervalSec 간격으로 최대 MaxReconnectRetries 시도.'},
            {'kind': 'variable', 'sig': 'TQueue<FNetCommand, EQueueMode::Mpsc> InboundCommandQueue',
             'desc': '메인 스레드 → 워커 스레드 명령 큐.'},
            {'kind': 'variable', 'sig': 'TQueue<FNetEvent, EQueueMode::Spsc> OutboundEventQueue',
             'desc': '워커 → 메인 스레드 이벤트 큐.'},
            {'kind': 'variable', 'sig': 'int32 MaxReconnectRetries=10, float ReconnectIntervalSec=3',
             'desc': '재접속 정책.'},
        ],
    },

    # ---------------- UI ----------------
    {
        'path': 'UI/NetworkInstance.h / .cpp',
        'summary': 'UGameInstance 서브클래스이자 FTickableGameObject. ClientNetworking 인스턴스 보유, 매 프레임 PumpEvents 호출, UI 흐름·원격 캐릭터 관리.',
        'items': [
            {'kind': 'class', 'sig': 'UNetworkInstance : public UGameInstance, public FTickableGameObject',
             'desc': '게임 전역에서 살아있는 네트워크 컨테이너.'},
            {'kind': 'function', 'sig': 'virtual void Init() override',
             'desc': '델리게이트 바인딩 후 Client->Start(IP, 9000) 호출.'},
            {'kind': 'function', 'sig': 'virtual void Tick(float) override',
             'desc': '매 프레임 Client->PumpEvents()를 호출해 워커 이벤트를 게임 스레드로 끌어온다.'},
            {'kind': 'function', 'sig': 'void ShowLoginHUD()',
             'desc': '로그인 위젯을 화면에 띄운다.'},
            {'kind': 'function', 'sig': 'void TryLogin(FString, FString) / TryRegister(FString, FString)',
             'desc': '로그인/회원가입 패킷 전송 래퍼.'},
            {'kind': 'function', 'sig': 'void CreateRoom() / JoinRoom(int32) / RequestReady() / RequestGameStart()',
             'desc': '로비/방 단계 요청 송신.'},
            {'kind': 'function', 'sig': 'void SelectCharacterAndReady(int32 SelectedRoleType)',
             'desc': '역할 선택 + 레디 처리(블루프린트에서 호출).'},
            {'kind': 'function', 'sig': 'void SendMoveInputToServer(const FMovePacket&)',
             'desc': '캐릭터 이동 입력을 서버에 전달.'},
            {'kind': 'function', 'sig': 'void HandleSnapshotReceived(const TArray<GameData>&)',
             'desc': '서버 스냅샷을 UID별로 분배. 로컬 플레이어는 트랜스폼 동기화, 원격 플레이어는 EnsureRemoteCharacter로 생성/갱신.'},
            {'kind': 'function', 'sig': 'AMyCharacter* EnsureRemoteCharacter(const GameData&)',
             'desc': '원격 플레이어 액터를 생성/조회한다.'},
            {'kind': 'function', 'sig': 'AMyCharacter* FindCharacterByUID(int32 UID) const',
             'desc': 'UID로 캐릭터 검색.'},
            {'kind': 'function', 'sig': 'void HandleGameStart()',
             'desc': '게임 시작 패킷 수신 시 InGameLevel을 OpenLevel.'},
            {'kind': 'function', 'sig': 'void HandleConnected() / HandleConnectFailed() / HandleDisconnected()',
             'desc': '연결 상태 콜백.'},
            {'kind': 'function', 'sig': 'void HandleAttackActionReceived / HandleDamageApplied / HandleStatusUpdated / HandleStateChanged / HandleRespawned',
             'desc': '인게임 패킷을 캐릭터로 전달.'},
            {'kind': 'variable', 'sig': 'TSharedPtr<ClientNetworking> Client',
             'desc': '워커 스레드 파사드.'},
            {'kind': 'variable', 'sig': 'TSubclassOf<UUserWidget> LoginWidgetClass / LobbyWidgetClass',
             'desc': '로그인·로비 위젯 클래스(에디터 노출).'},
            {'kind': 'variable', 'sig': 'TSubclassOf<URoomWidget> RoomWidgetClass',
             'desc': '대기실 위젯 클래스.'},
            {'kind': 'variable', 'sig': 'TSoftObjectPtr<UWorld> InGameLevel',
             'desc': '게임 시작 시 열 인게임 레벨.'},
            {'kind': 'variable', 'sig': 'TSubclassOf<AMyCharacter> RemoteCharacterClass',
             'desc': '원격 플레이어 인스턴스를 생성할 때 사용할 클래스.'},
            {'kind': 'variable', 'sig': 'TMap<int32, TWeakObjectPtr<AMyCharacter>> RemoteCharacters',
             'desc': 'UID → 캐릭터 약참조 맵.'},
            {'kind': 'variable', 'sig': 'FString ServerIPAddress="127.0.0.1"',
             'desc': '접속 대상 서버 IP(Config 가능).'},
            {'kind': 'variable', 'sig': 'int32 MaxRetryCount=10',
             'desc': '연결 재시도 한도.'},
            {'kind': 'variable', 'sig': 'TArray<GameData> PendingSnapshotList / bool bHasPendingSnapshot',
             'desc': '로컬 플레이어 준비 전에 도착한 스냅샷 캐싱.'},
        ],
    },
    {
        'path': 'UI/LoginWidget.h / .cpp',
        'summary': '로그인 화면. ID/PW 입력 박스와 로그인/회원가입 버튼을 보유하며 NetworkInstance를 통해 패킷을 보낸다.',
        'items': [
            {'kind': 'class', 'sig': 'ULoginWidget : public UUserWidget', 'desc': '로그인 위젯.'},
            {'kind': 'function', 'sig': 'void OnLoginButtonClicked() / OnRegisterButtonClicked()',
             'desc': 'NetworkInstance::TryLogin/TryRegister 호출.'},
            {'kind': 'variable', 'sig': 'UEditableTextBox* IDBox / PWBox',
             'desc': 'ID/PW 입력 위젯.'},
        ],
    },
    {
        'path': 'UI/RobbyWidget.h / .cpp',
        'summary': '로비 화면. 방 목록을 표시하고 방 생성/입장 버튼을 제공한다.',
        'items': [
            {'kind': 'class', 'sig': 'URobbyWidget : public UUserWidget', 'desc': '로비 위젯.'},
            {'kind': 'function', 'sig': 'void RefreshRoomList(const TArray<FRoomInfoData>&)',
             'desc': '서버가 보낸 방 목록으로 UI를 갱신.'},
            {'kind': 'function', 'sig': 'void OnCreateRoomClicked() / OnJoinRoomClicked(int32 RoomID)',
             'desc': '버튼 콜백.'},
        ],
    },
    {
        'path': 'UI/RoomWidget.h / .cpp',
        'summary': '대기실 화면. 멤버 슬롯과 레디/시작 버튼, 캐릭터 선택 위젯을 호스팅한다.',
        'items': [
            {'kind': 'class', 'sig': 'URoomWidget : public UUserWidget', 'desc': '방 화면.'},
            {'kind': 'function', 'sig': 'void UpdateMembers(const TArray<FRoomMemberInfo>&)',
             'desc': '서버 RoomMember 정보를 화면에 반영.'},
            {'kind': 'function', 'sig': 'void OnReadyClicked() / OnStartClicked()',
             'desc': '레디 토글 / 게임 시작 요청.'},
            {'kind': 'variable', 'sig': 'static const int32 MAXPLAYER = 6',
             'desc': '한 방의 최대 인원.'},
        ],
    },
    {
        'path': 'UI/RoomEnterWidget.h / .cpp',
        'summary': '방 멤버 슬롯 한 칸을 표현하는 작은 위젯.',
        'items': [
            {'kind': 'class', 'sig': 'URoomEnterWidget : public UUserWidget', 'desc': '슬롯 위젯.'},
            {'kind': 'function', 'sig': 'void SetMemberInfo(const FRoomMemberInfo&)',
             'desc': '플레이어 이름/레디 상태 표시.'},
        ],
    },
    {
        'path': 'UI/RoomMemberWidget.h / .cpp',
        'summary': 'RoomEnterWidget의 또 다른 표현. 한 명의 멤버 정보를 출력한다.',
        'items': [
            {'kind': 'class', 'sig': 'URoomMemberWidget : public UUserWidget', 'desc': '멤버 정보 위젯.'},
        ],
    },
    {
        'path': 'UI/CharacterInfoWidget.h / .cpp',
        'summary': '역할 선택 패널(Striker / Guardian / Manipulator 버튼).',
        'items': [
            {'kind': 'class', 'sig': 'UCharacterInfoWidget : public UUserWidget', 'desc': '역할 선택 위젯.'},
            {'kind': 'function', 'sig': 'void OnSelectStriker() / OnSelectGuardian() / OnSelectManipulator()',
             'desc': '각 역할 버튼 클릭 콜백 → NetworkInstance::SelectCharacterAndReady.'},
        ],
    },

    # ---------------- GameState ----------------
    {
        'path': 'GameState/InGame_GameState.h / .cpp',
        'summary': '인게임 라운드/페이즈 상태를 보유하는 GameState. 1Hz Countdown으로 GetElapsedPlayTime을 기준으로 페이즈 전환을 결정.',
        'items': [
            {'kind': 'class', 'sig': 'AInGame_GameState : public AGameStateBase', 'desc': '서버 권위 GameState.'},
            {'kind': 'enum', 'sig': 'ERoundState { Waiting, Playing, Finished }',
             'desc': '라운드 상태.'},
            {'kind': 'enum', 'sig': 'EMapPhase { None, Phase1, Phase2, Phase3, End }',
             'desc': '맵 단계.'},
            {'kind': 'function', 'sig': 'void CountdownTick()',
             'desc': '1초마다 호출되어 페이즈 변경/종료를 결정.'},
            {'kind': 'function', 'sig': 'void UpdatePhase()',
             'desc': '경과 시간 기반으로 CurrentPhase를 갱신.'},
            {'kind': 'variable', 'sig': 'float Phase1Time / Phase2Time / Phase3Time',
             'desc': '각 페이즈의 지속 시간.'},
            {'kind': 'variable', 'sig': 'ERoundState RoundState / EMapPhase CurrentPhase',
             'desc': '현재 라운드/페이즈 상태(복제됨).'},
        ],
    },

    # ---------------- Map ----------------
    {
        'path': 'Map/MapPhaseManager.h / .cpp',
        'summary': 'GameState를 폴링해 페이즈/라운드 상태가 바뀌면 델리게이트를 브로드캐스트하는 헬퍼 액터.',
        'items': [
            {'kind': 'class', 'sig': 'AMapPhaseManager : public AActor', 'desc': '페이즈 변경 알림자.'},
            {'kind': 'function', 'sig': 'virtual void Tick(float) override',
             'desc': '캐싱된 GameState를 매 틱 폴링.'},
            {'kind': 'function', 'sig': 'void UpdateFromGameState()',
             'desc': '값이 바뀌면 OnMapPhaseChanged / OnRoundStateChanged를 발화.'},
            {'kind': 'delegate', 'sig': 'FOnMapPhaseChanged(EMapPhase NewPhase)',
             'desc': '페이즈 전환 통지.'},
            {'kind': 'delegate', 'sig': 'FOnRoundStateChanged(ERoundState NewState)',
             'desc': '라운드 상태 전환 통지.'},
        ],
    },
    {
        'path': 'Map/BreakableActor.h / .cpp',
        'summary': '단순 파괴 가능 액터. 데미지 누적·상태 전이.',
        'items': [
            {'kind': 'class', 'sig': 'ABreakableActor : public AActor', 'desc': '파괴 가능 베이스.'},
            {'kind': 'enum', 'sig': 'EBreakableActorState { Idle, Active, Breaking, Broken }',
             'desc': '내구 상태 머신.'},
            {'kind': 'function', 'sig': 'void ApplyBreakableDamage(float Amount)',
             'desc': '내구도를 차감하고 0 이하가 되면 BreakActor 호출.'},
            {'kind': 'function', 'sig': 'void BreakActor()',
             'desc': '파편 스폰 등 파괴 처리.'},
            {'kind': 'variable', 'sig': 'float MaxDurability=100.f, CurrentDurability',
             'desc': '내구도 값.'},
        ],
    },
    {
        'path': 'Map/PreFracturedActor.h / .cpp',
        'summary': '청크(Chunk) 기반 사전-파괴 액터. 인접 그래프 자동 생성, 앵커 시스템, 연쇄 파괴(원래 데미지의 30%) 전파.',
        'items': [
            {'kind': 'class', 'sig': 'APreFracturedActor : public AActor', 'desc': '청크 분할 파괴 액터.'},
            {'kind': 'struct', 'sig': 'FPreFracturedChunkData',
             'desc': 'ChunkIndex / Neighbors / CurrentDamage / BreakThreshold(=100) / bBroken / bAnchored.'},
            {'kind': 'function', 'sig': 'void AutoBuildNeighborGraph()',
             'desc': '청크 간 거리 임계값 기준으로 인접 그래프를 자동 구성.'},
            {'kind': 'function', 'sig': 'void AutoSetAnchoredChunks()',
             'desc': 'Z 축 기준 하단 청크들을 앵커로 마킹.'},
            {'kind': 'function', 'sig': 'void ApplyDamageToChunk(int32 Index, float Amount)',
             'desc': '청크에 데미지 적용. 인접 청크에는 NeighborDamageRatio(0.3) 비율로 전파.'},
            {'kind': 'function', 'sig': 'void BreakChunk(int32 Index)',
             'desc': '청크 메시 디태치 + 물리 활성화.'},
            {'kind': 'function', 'sig': 'void DropUnsupportedChunks()',
             'desc': '앵커 청크에서 BFS로 도달 가능한 청크만 유지, 끊긴 청크는 낙하.'},
            {'kind': 'variable', 'sig': 'float NeighborDamageRatio = 0.3f',
             'desc': '연쇄 파괴 비율.'},
        ],
    },
    {
        'path': 'Map/Building/DebrisSpawner.h / .cpp',
        'summary': '페이즈에 따라 빈도/개수가 달라지는 잔해 스포너. (Phase1 6~10s, Phase2 3~6s, Phase3 2~4s)',
        'items': [
            {'kind': 'class', 'sig': 'ADebrisSpawner : public AActor', 'desc': '잔해 스폰 컨트롤러.'},
            {'kind': 'function', 'sig': 'virtual void Tick(float) override',
             'desc': 'Accumulator를 누적해 Interval 도달 시 스폰.'},
            {'kind': 'function', 'sig': 'void SpawnDebris()',
             'desc': '현재 페이즈 설정에 따라 1~2개의 잔해 액터를 스폰.'},
        ],
    },
    {
        'path': 'Map/Building/LargeDebrisActor.h / .cpp',
        'summary': '낙하하는 대형 잔해. 자체 중력/최대 낙하 속도를 시뮬레이션.',
        'items': [
            {'kind': 'class', 'sig': 'ALargeDebrisActor : public AActor', 'desc': '대형 낙하물.'},
            {'kind': 'function', 'sig': 'virtual void Tick(float) override',
             'desc': '중력 가속 적용 후 위치 갱신, 충돌 시 LandAndFracture.'},
            {'kind': 'variable', 'sig': 'float GravityAcceleration=980.f, MaxFallSpeed=4000.f',
             'desc': '낙하 시뮬레이션 파라미터.'},
        ],
    },
    {
        'path': 'Map/Building/LargeDebrisController.h / .cpp',
        'summary': '대형 잔해 스폰 시점/위치를 페이즈에 따라 조정한다.',
        'items': [
            {'kind': 'class', 'sig': 'ALargeDebrisController : public AActor', 'desc': '대형 잔해 매니저.'},
        ],
    },
    {
        'path': 'Map/IceCave/IceFloorTile.h / .cpp',
        'summary': '얼음 동굴 맵의 바닥 타일. 정상/금감/깨짐 상태로 전이된다.',
        'items': [
            {'kind': 'class', 'sig': 'AIceFloorTile : public AActor', 'desc': '바닥 타일 액터.'},
            {'kind': 'function', 'sig': 'void SetCracked() / StartBreaking() / Break()',
             'desc': '상태 전이 및 비주얼/콜리전 토글.'},
        ],
    },
    {
        'path': 'Map/IceCave/IcicleActor.h / .cpp',
        'summary': '천장에서 떨어지는 고드름. 경고 → 낙하 → 파괴 단계.',
        'items': [
            {'kind': 'class', 'sig': 'AIcicleActor : public AActor', 'desc': '고드름 액터.'},
            {'kind': 'function', 'sig': 'void StartWarning() / StartFalling() / Break()',
             'desc': '서버 이벤트에 따른 상태 전이.'},
        ],
    },
    {
        'path': 'Map/IceCave/IceMapController.h / .cpp',
        'summary': '얼음 동굴 맵 전반의 오브젝트 등록/검색을 담당.',
        'items': [
            {'kind': 'class', 'sig': 'AIceMapController : public AActor', 'desc': '얼음 동굴 컨트롤러.'},
            {'kind': 'function', 'sig': 'AIcicleActor* FindIcicle(int32 ID) / AIceFloorTile* FindTile(int32 ID)',
             'desc': '맵 이벤트 패킷이 가리키는 오브젝트를 ID로 검색.'},
        ],
    },
]


# ============================================================
# 서버 파일 데이터
# ============================================================

SERVER_FILES = [
    {
        'path': 'main.cpp',
        'summary': '서버 진입점. WSAStartup → IOCPServer 초기화/구동 → 60fps 게임 프레임 루프.',
        'items': [
            {'kind': 'function', 'sig': 'int main()',
             'desc': 'IOCPServer를 9000 포트, 최대 3000 세션으로 초기화하고 구동, deltaTime 기반 60fps 루프에서 GameFrameProtocol 호출.'},
            {'kind': 'const', 'sig': 'const int PORT = 9000 / MAX_CLIENT = 3000',
             'desc': '리슨 포트와 최대 동시 세션 수.'},
        ],
    },
    {
        'path': 'server.h / server.cpp',
        'summary': 'IOCP 기반 메인 서버 클래스. WorkerThread × CPU*2 + AcceptThread + DBWorkerThread를 운용한다.',
        'items': [
            {'kind': 'class', 'sig': 'class IOCPServer',
             'desc': 'IOCP 핸들과 SessionManager/RoomManager/DBHelper 컴포지션을 보유.'},
            {'kind': 'function', 'sig': 'bool Init()',
             'desc': 'WSAStartup, CreateIoCompletionPort, bind, listen 수행.'},
            {'kind': 'function', 'sig': 'void Start()',
             'desc': 'Worker(CPU*2)·Accept·DBWorker 스레드를 모두 기동.'},
            {'kind': 'function', 'sig': 'void Shutdown()',
             'desc': '소켓 닫기 + WSACleanup.'},
            {'kind': 'function', 'sig': 'static unsigned WINAPI WorkerThread(void*)',
             'desc': 'GetQueuedCompletionStatus 결과에 따라 OnRecv/OnSend 디스패치.'},
            {'kind': 'function', 'sig': 'static unsigned WINAPI AcceptThread(void*)',
             'desc': 'accept loop. 새 소켓 도착 시 OnConnect 호출.'},
            {'kind': 'function', 'sig': 'static unsigned WINAPI DBWorkerThread(void*)',
             'desc': 'condition_variable로 m_DBLoginQueue를 대기. Login/Register 처리 후 결과 패킷 송신.'},
            {'kind': 'function', 'sig': 'void OnConnect(SOCKET)',
             'desc': '신규 클라이언트 소켓을 IOCP에 묶고 PKT_S2C_ACCESS_ALLOW 송신, WSARecv 게시.'},
            {'kind': 'function', 'sig': 'void OnRecv(Session*, DWORD bytes)',
             'desc': '링버퍼에 누적 → 헤더 길이 분리 → PacketProcess 호출.'},
            {'kind': 'function', 'sig': 'void OnSend(Session*, DWORD bytes)',
             'desc': '송신 완료 처리. 큐에 남은 패킷이 있으면 다음 WSASend 게시.'},
            {'kind': 'function', 'sig': 'void SendPacket(int sessionID, int packetID, const char* data, int len)',
             'desc': '헤더 + 데이터를 합쳐 sendQueue에 push 후 SendProtocol 호출.'},
            {'kind': 'function', 'sig': 'void SendProtocol(Session*)',
             'desc': '실제 WSASend 호출. isSending 플래그로 중복 송신 방지.'},
            {'kind': 'function', 'sig': 'void BroadcastRoomList()',
             'desc': '모든 LOBBY 상태 세션에 PKT_S2C_ROOM_UPDATE 전송.'},
            {'kind': 'function', 'sig': 'void BroadcastRoomInfo(Session*)',
             'desc': '특정 방의 멤버 변화(Ready 토글 등)를 PKT_S2C_ROOM_INFO_BRD로 브로드캐스트.'},
            {'kind': 'function', 'sig': 'bool CreateRoomTry / JoinRoomTry / GameStartTry(Session*)',
             'desc': 'PacketProcessor → RoomManager로 위임하는 얇은 래퍼.'},
            {'kind': 'function', 'sig': 'void GameFrameProtocol(float deltaTime)',
             'desc': '60fps 루프에서 m_RoomManager->UpdateRooms(deltaTime) 호출.'},
            {'kind': 'function', 'sig': 'void PushDBTask(const DBData&)',
             'desc': 'DB 큐에 작업 푸시 후 condition_variable 통지.'},
            {'kind': 'variable', 'sig': 'HANDLE m_hIOCP / SOCKET m_ListenSocket',
             'desc': 'IOCP 핸들과 리슨 소켓.'},
            {'kind': 'variable', 'sig': 'SessionManager* m_SessionManager / RoomManager* m_RoomManager / DBHelper* m_DBHelper',
             'desc': '서버의 핵심 구성요소.'},
            {'kind': 'variable', 'sig': 'std::queue<DBData> m_DBLoginQueue / std::mutex / std::condition_variable',
             'desc': 'DB 작업 큐와 동기화 객체.'},
        ],
    },
    {
        'path': 'session.h',
        'summary': '세션 구조체와 IO 보조 자료. 링버퍼·OverlappedEx·세션 상태 등.',
        'items': [
            {'kind': 'struct', 'sig': 'struct s_ringbuf { char buf[BUF_SIZE]; int head, tail, size; }',
             'desc': '수신 데이터 누적용 링버퍼(BUF_SIZE=10240).'},
            {'kind': 'function', 'sig': 'RingBufPush / Peek / Pop',
             'desc': '랩어라운드 처리 포함 링버퍼 헬퍼.'},
            {'kind': 'struct', 'sig': 'struct OverlappedEx { OVERLAPPED ov; WSABUF wsabuf; IO_OPERATION type; }',
             'desc': 'IOCP 식별용 확장 OVERLAPPED.'},
            {'kind': 'enum', 'sig': 'IO_OPERATION { RECV, SEND, AWAIT }',
             'desc': '완료 알림 분류.'},
            {'kind': 'enum', 'sig': 'ESessionState { LOGIN, LOBBY, ROOM, INGAME }',
             'desc': '세션의 큰 흐름 상태.'},
            {'kind': 'struct', 'sig': 'struct MoveIntent { float Right, Forward, Yaw; bool bHasInput; }',
             'desc': '서버에서 마지막으로 받은 이동 입력 의도.'},
            {'kind': 'struct', 'sig': 'struct Session',
             'desc': 'sessionID, socket, isConnected, roomID, playerUID, playerName, gameDatas, recvBuffer, sendQueue 등.'},
        ],
    },
    {
        'path': 'SessionManager.h / .cpp',
        'summary': 'MAXCLIENT(=3000) 사이즈의 세션 풀을 관리하는 싱글톤. FreeSessionQueue 기반 슬롯 재사용.',
        'items': [
            {'kind': 'class', 'sig': 'class SessionManager (singleton)',
             'desc': '세션 풀과 free 큐 보유.'},
            {'kind': 'function', 'sig': 'void Init()',
             'desc': 'MAXCLIENT 만큼 세션을 사전 할당.'},
            {'kind': 'function', 'sig': 'Session* AcceptNewClient(SOCKET)',
             'desc': 'free 큐에서 슬롯을 꺼내 소켓·상태를 초기화 후 반환.'},
            {'kind': 'function', 'sig': 'void DisconnectClient(int clientID)',
             'desc': '3단계 처리: 소켓 닫기 → RoomManager에 leave 알림 → 슬롯 free 큐 반환.'},
            {'kind': 'function', 'sig': 'void SetState(int sessionID, ESessionState)',
             'desc': '세션 상태 전이.'},
            {'kind': 'function', 'sig': 'Session* GetSession(int sessionID)',
             'desc': '연결 상태 검사 후 세션 반환.'},
            {'kind': 'variable', 'sig': 'std::vector<Session*> m_Sessions / std::queue<int> m_FreeSessionQueue / std::mutex m_SessionLock',
             'desc': '세션 풀과 동기화 객체.'},
            {'kind': 'const', 'sig': 'static const int MAXCLIENT = 3000',
             'desc': '동시 접속 한도.'},
        ],
    },
    {
        'path': 'Packet.h',
        'summary': '패킷 직렬화/역직렬화 유틸과 패킷 ID·구조체 정의.',
        'items': [
            {'kind': 'class', 'sig': 'class PacketReader',
             'desc': '바이트 버퍼에서 안전하게 값을 읽는 헬퍼. Read<T>, ReadString(UE FString ANSI/UTF-16, 음수 길이 처리).'},
            {'kind': 'enum', 'sig': 'enum PacketID',
             'desc': '서버↔클라 양쪽이 공유하는 패킷 ID. 클라이언트와 동일한 범위 규약.'},
            {'kind': 'struct', 'sig': '#pragma pack(1) 모든 패킷 구조체',
             'desc': 'PacketHeader / LoginPacket / RoomPacket / GameDataPacket / MovePacket / DamageApplyPacket / StateChangePacket / RespawnPacket / RoleChangePacket / MapEventPacket / SpawnObjectPacket / PhaseChangePacket / SyncGameTimePacket / AttackActionPacket / SyncAnimationPacket 등.'},
        ],
    },
    {
        'path': 'PacketProcessor.h / .cpp',
        'summary': 'packetID → 핸들러 함수 포인터 테이블. 서버 디스패치의 중심.',
        'items': [
            {'kind': 'class', 'sig': 'class PacketProcessor', 'desc': '핸들러 맵 보유.'},
            {'kind': 'function', 'sig': 'void InitHandler()',
             'desc': '모든 PKT_C2S_* ID에 대해 Handle_* 함수를 등록.'},
            {'kind': 'function', 'sig': 'void Process(IOCPServer*, Session*, int packetID, std::vector<char>& data)',
             'desc': 'ID로 핸들러를 찾아 PacketReader 인스턴스로 호출.'},
            {'kind': 'function', 'sig': 'static void Handle_LoginReq / Handle_RegisterReq',
             'desc': 'ID/PW 추출 후 PushDBTask로 DB 워커에 위임.'},
            {'kind': 'function', 'sig': 'static void Handle_Room_CreateReq / Handle_Room_JoinReq',
             'desc': 'CreateRoomTry / JoinRoomTry 호출.'},
            {'kind': 'function', 'sig': 'static void Handle_Game_StartReq',
             'desc': 'GameStartTry 호출.'},
            {'kind': 'function', 'sig': 'static void Handle_Character_SelectReq',
             'desc': 'roleType 0~2 검증 → session.gameDatas.roleType 업데이트 → 같은 방에 RoleChangePacket 브로드캐스트.'},
            {'kind': 'function', 'sig': 'static void Handle_Game_ReadyReq',
             'desc': 'isReady 토글 후 BroadcastRoomInfo.'},
            {'kind': 'function', 'sig': 'static bool Handle_Move_KeyInput',
             'desc': 'MovePacket 파싱·정규화(±1 클램프, NaN 가드) 후 Session::LastMoveIntent 갱신.'},
            {'kind': 'function', 'sig': 'static void Handle_Attack_KeyInput',
             'desc': 'GameLogicHelper로 룸·로직 검증 후 GameLogic::HandleAttackInput 호출.'},
            {'kind': 'function', 'sig': 'static GameLogic* GameLogicHelper(server, session)',
             'desc': '세션이 PLAYING 상태 방에 속해 있는지 검사 후 GameLogic 반환.'},
            {'kind': 'variable', 'sig': 'std::unordered_map<int, HandlerFunc> m_FuncHandlerMap',
             'desc': '디스패치 테이블.'},
        ],
    },
    {
        'path': 'RoomManager.h / .cpp',
        'summary': 'Room(최대 6명, 최대 500개)과 그 매니저(싱글톤). 방 생성·입장·퇴장·게임 시작·매 프레임 갱신.',
        'items': [
            {'kind': 'class', 'sig': 'class Room',
             'desc': '한 매치를 표현. m_Members, m_GameLogic, 방장 sessionID, UsedSlots[6].'},
            {'kind': 'function', 'sig': 'void InitRoom(int id, Session* first, IOCPServer*)',
             'desc': '방 기본 필드 초기화.'},
            {'kind': 'function', 'sig': 'void InitGameLogic(GameLogic*)',
             'desc': '플레이어 등록 + InitCharacter 호출 + 라운드 시작.'},
            {'kind': 'function', 'sig': 'void InitCharacter(Session*, GameLogic*)',
             'desc': '슬롯 기반 팀/스폰/요/HP 셋업, ApplyRoleStats 호출.'},
            {'kind': 'function', 'sig': 'bool addMember(Session*) / void RemoveMember(int)',
             'desc': '슬롯 할당/해제, 첫 멤버는 방장으로 등록.'},
            {'kind': 'function', 'sig': 'int AllocateRoomSlot()',
             'desc': '0~5 중 빈 슬롯 검색.'},
            {'kind': 'function', 'sig': 'void TransferOwnership()',
             'desc': '방장 퇴장 시 다음 멤버로 방장 이전.'},
            {'kind': 'function', 'sig': 'int TeamCalculateBySlot(int) const',
             'desc': '슬롯 0-2=팀0, 3-5=팀1.'},
            {'kind': 'function', 'sig': 'Vector3 GetRespawnLocation(int slot)',
             'desc': '6개 고정 스폰 좌표 테이블에서 반환.'},
            {'kind': 'function', 'sig': 'float GetSpawnYawBySlot(int slot) const',
             'desc': '팀에 따라 0° 또는 180°.'},
            {'kind': 'function', 'sig': 'void UpdateGameLogic(float dt)',
             'desc': 'PLAYING 상태일 때 GameLogic::Update 호출.'},
            {'kind': 'function', 'sig': 'bool BroadcastGameDatas()',
             'desc': '연결된 멤버의 GameData 스냅샷을 PKT_S2C_SNAPSHOT_NOTICE로 송신. 인원 0이면 false 반환(방 제거 신호).'},
            {'kind': 'function', 'sig': 'std::vector<RoomMemberPacket> GetMemberInfoList()',
             'desc': '대기실 UI용 멤버 목록.'},
            {'kind': 'function', 'sig': 'void BroadcastToMembers(int packetID, const char*, int len, int excludeSessionID=-1)',
             'desc': '방 내 모든(혹은 일부 제외) 멤버에 패킷 전송.'},
            {'kind': 'class', 'sig': 'class RoomManager (singleton)',
             'desc': '모든 방을 보유.'},
            {'kind': 'function', 'sig': 'bool CreateRoom(Session*) / bool JoinRoom(Session*, int) / void LeaveRoom(Session*) / void LeaveRoomByDisconnect(int, int)',
             'desc': '방 생성/입장/퇴장 처리. 마지막 사람이 나가면 방 삭제, 방장 퇴장 시 이전, BroadcastRoomList/BroadcastRoomInfo 호출.'},
            {'kind': 'function', 'sig': 'void GameStart(Session*)',
             'desc': '방장만 호출 가능. 전원 Ready 검증 후 ERoomState::PLAYING으로 전이, GameLogic 생성·Init·PKT_S2C_GAME_START_BRD 전송.'},
            {'kind': 'function', 'sig': 'void UpdateRooms(float dt)',
             'desc': '모든 방을 순회하며 UpdateGameLogic + BroadcastGameDatas. 빈 방은 DestroyRoom.'},
            {'kind': 'function', 'sig': 'std::vector<RoomPacket> GetRoomList()',
             'desc': '대기 중(WAITING) 방만 추려 로비 UI에 노출.'},
            {'kind': 'const', 'sig': 'static const int MaxMember=6 / MaxRoom=500',
             'desc': '한 방 인원 한도와 동시 방 수 한도.'},
        ],
    },
    {
        'path': 'GameLogic.h / .cpp',
        'summary': '인게임 핵심 로직. HP/State/Role/Item/Combat, 충돌, 빌딩맵·얼음동굴맵 페이즈·기믹을 모두 담는다.',
        'items': [
            {'kind': 'class', 'sig': 'class GameLogic',
             'desc': '한 룸의 인게임 상태 머신. ownerRoom과 players 맵을 보유.'},
            {'kind': 'function', 'sig': 'void Update(float dt)',
             'desc': 'PLAYING 상태에서 1초 카운트다운 및 맵 타입별(빌딩=1 / 얼음동굴=2) 업데이트.'},
            {'kind': 'function', 'sig': 'void StartGameRound() / EndGameRound() / CountdownTick()',
             'desc': '라운드 시작·종료, 1초 단위 페이즈 전환, 종료 판정.'},
            {'kind': 'function', 'sig': 'void HandlePhaseChanged(int newPhase)',
             'desc': 'PhaseChangePacket을 모든 멤버에 브로드캐스트.'},
            {'kind': 'function', 'sig': 'void BroadcastGameTime / BroadcastDamageApply / BroadcastStatusUpdate / BroadcastStateChange / BroadcastRespawn / BroadcastRoleChange / BroadcastAttackAction',
             'desc': '게임 타이머·데미지·HP·상태·리스폰·역할·공격을 룸 멤버에 송신.'},
            {'kind': 'function', 'sig': 'void ApplyDamage / Heal / ResetHP / SetCurrentHP',
             'desc': 'HP 산술과 클램프, 사망 트리거.'},
            {'kind': 'function', 'sig': 'void HandleDeath / HandleRespawn',
             'desc': '사망 시 characterState=1, 리스폰 시 슬롯 위치로 복귀.'},
            {'kind': 'function', 'sig': 'void SetRole / ApplyRoleStats(int sessionID)',
             'desc': '역할별 baseWalkSpeed=500*Mult, MaxHP(Striker 100 / Guardian 200 / Manipulator 120) 적용.'},
            {'kind': 'function', 'sig': 'float GetRoleSpeedMultiplier(int)',
             'desc': 'Striker 1.2 / Guardian 0.8 / Manipulator 1.0.'},
            {'kind': 'function', 'sig': 'void HandleAttackInput(int sessionID)',
             'desc': '연결/생존/UID 검증 후 BroadcastAttackAction.'},
            {'kind': 'function', 'sig': 'void UpdateBuildingMap(float dt)',
             'desc': 'Phase1+ 잔해 스포너, Phase2/3 트리거(1회). DebrisSpawnConfig를 phase별로 사용.'},
            {'kind': 'function', 'sig': 'void UpdateDebrisSpawner / SpawnDebrisByPhase / TriggerBuildingPhase2 / TriggerBuildingPhase3',
             'desc': '소형 잔해 누적 스폰과 대형 잔해 페이즈 트리거 송신.'},
            {'kind': 'function', 'sig': 'void StartIceMap / UpdateIceCaveMap / EnterIcePhase2 / EnterIcePhase3',
             'desc': '고드름 20개·바닥 타일 30개 초기화. Phase2 고드름 3s 간격, Phase3 1.5s+바닥 4s.'},
            {'kind': 'function', 'sig': 'void TriggerRandomIcicle / StartIcicleWarning / StartIcicleFalling / BreakIcicle',
             'desc': 'Idle 상태 고드름 중 랜덤 선택 → Warning(타이머) → Falling → Broken 단계 송신.'},
            {'kind': 'function', 'sig': 'void TriggerRandomFloorTile / SetFloorCracked / StartFloorBreaking / BreakFloor',
             'desc': '바닥 타일 상태 머신 진행과 MapEventPacket 송신.'},
            {'kind': 'function', 'sig': 'void UpdatePlayerMovement(Session*, float dt)',
             'desc': '서버 권위 이동 시뮬레이션(요 기반 forward/right 합성, 정규화, 충돌 해소). 현재는 아직 호출되지 않음(주석 처리).'},
            {'kind': 'function', 'sig': 'float GetCollisionRadius(int roleType) const',
             'desc': 'Striker/Manipulator 45, Guardian 55.'},
            {'kind': 'function', 'sig': 'bool CanOccupyPosition / Vector3 ResolveMovementWithCollision',
             'desc': '충돌 검사 자리. 현재는 desiredPos를 그대로 반환하는 임시 구현.'},
            {'kind': 'variable', 'sig': 'std::map<int, Session*> players',
             'desc': 'sessionID → Session* 매핑.'},
            {'kind': 'variable', 'sig': 'ERoundState roundState / int currentMapPhase / int currentGameTime',
             'desc': '라운드 상태와 페이즈/시간.'},
            {'kind': 'variable', 'sig': 'int phase1Time / phase2Time / phase3Time',
             'desc': '페이즈 길이.'},
            {'kind': 'variable', 'sig': 'DebrisSpawnConfig debrisPhaseConfigs[3]',
             'desc': 'Phase1/2/3 별 min/max 간격·개수.'},
            {'kind': 'variable', 'sig': 'std::vector<IcicleData> icicles / std::vector<IceFloorTileData> floorTiles',
             'desc': '얼음 동굴 기믹 인스턴스.'},
            {'kind': 'variable', 'sig': 'float MapMinX=-5000 / MapMaxX=5000 / FixedGroundZ=1200',
             'desc': '맵 경계와 고정 지면 Z 값.'},
            {'kind': 'variable', 'sig': 'Room* ownerRoom',
             'desc': '소속 방 역참조.'},
        ],
    },
    {
        'path': 'Database.h / .cpp',
        'summary': 'ODBC 기반 DB 헬퍼. server_config.ini의 ConnectionString을 읽어 SQLDriverConnect로 접속.',
        'items': [
            {'kind': 'class', 'sig': 'class DBHelper (singleton)',
             'desc': 'SQLHENV/SQLHDBC 보유.'},
            {'kind': 'function', 'sig': 'bool Connect() / void Disconnect()',
             'desc': 'ODBC 환경/연결 핸들 할당, INI에서 연결 문자열 로드 후 접속/해제.'},
            {'kind': 'function', 'sig': 'bool CheckLogin(userID, userPW, int& playerUID)',
             'desc': '저장 프로시저 SP_LoginAccess 호출. 결과 0이면 실패, 그 외는 AccountUID 반환.'},
            {'kind': 'function', 'sig': 'bool CreateAccount(userID, userPW)',
             'desc': '저장 프로시저 SP_CreateAccount 호출. -1이면 ID 중복.'},
            {'kind': 'function', 'sig': 'bool IsValidUserID(const std::wstring&)',
             'desc': '영문자 시작 + 4-12 영숫자 + 예약어(admin/gm/master 등) 부분 일치 차단.'},
            {'kind': 'function', 'sig': 'bool IsValidUserPW(const std::wstring&)',
             'desc': '4-12자 영숫자 정규식 검사.'},
            {'kind': 'function', 'sig': 'bool IsValidAccountString(const std::wstring&)',
             'desc': '범용 영숫자 4-12자 검사.'},
            {'kind': 'function', 'sig': 'void PrintError(SQLHANDLE, SQLSMALLINT)',
             'desc': 'SQLGetDiagRec로 ODBC 에러를 LOG_ERROR로 출력.'},
            {'kind': 'enum', 'sig': 'enum class EDBTaskType { LOGIN, REGISTER }',
             'desc': 'DB 워커 작업 종류.'},
            {'kind': 'struct', 'sig': 'struct DBData { int sessionID; std::wstring id, pw; EDBTaskType type; }',
             'desc': 'DB 워커 큐 메시지.'},
        ],
    },
    {
        'path': 'logger.h',
        'summary': '로깅 매크로와 일자별 로그 파일 정리.',
        'items': [
            {'kind': 'function', 'sig': 'void CleanupOldLogs()',
             'desc': 'ServerLog_YYYY-MM-DD.log 패턴(정규식) 14일 이상 경과 파일 삭제.'},
            {'kind': 'function', 'sig': 'std::string GetTimestamp()',
             'desc': '로그 라인용 타임스탬프 문자열.'},
            {'kind': 'macro', 'sig': 'LOG_INFO / LOG_WARN / LOG_ERROR',
             'desc': 'level + 타임스탬프 + 가변 인자 포맷팅 매크로.'},
        ],
    },
]


# ============================================================
# 문서 생성
# ============================================================

OUTPUT_PATH = "D:/Download/Claim_Of_Core_Project-MainClient/Claim_Of_Core_Project-MainClient/MainClient_Codes/Claim_Of_Core/Source/Claim_Of_Core_Documentation.pdf"


def build():
    doc = SimpleDocTemplate(
        OUTPUT_PATH, pagesize=A4,
        leftMargin=15 * mm, rightMargin=15 * mm,
        topMargin=15 * mm, bottomMargin=15 * mm,
        title="Claim of Core - 프로젝트 코드 문서",
        author="Claude Code"
    )

    flow = []

    # ----- 표지 -----
    flow.append(Spacer(1, 60 * mm))
    flow.append(P("Claim of Core", style_title))
    flow.append(P("프로젝트 코드 문서", style_title))
    flow.append(Spacer(1, 20 * mm))
    flow.append(P("Unreal Engine 5.7 기반 멀티플레이어 3인칭 액션 게임", style_body))
    flow.append(P("클라이언트(C++) + 전용 IOCP 서버(C++)", style_body))
    flow.append(Spacer(1, 8 * mm))
    flow.append(P("작성일: 2026-04-27", style_note))
    flow.append(PageBreak())

    # ----- 개요 -----
    flow.append(P("프로젝트 개요", style_h1))
    flow.append(P(
        "본 문서는 Claim of Core 프로젝트의 클라이언트 코드와 서버 코드에서 실제 사용되는 "
        "클래스 / 함수 / 변수를 파일 단위로 정리한 것이다. 각 항목에는 역할에 대한 간단한 "
        "설명을 함께 기재하여, 코드를 직접 보지 않고도 시스템의 큰 그림과 세부 책임을 파악할 수 있도록 한다.",
        style_body))
    flow.append(P("아키텍처 요약", style_h2))
    flow.append(P(
        "- 클라이언트는 Unreal Engine 5.7 C++ 모듈 1개(Claim_Of_Core)로 구성되며, "
        "표준 UE Replication 대신 별도의 커스텀 소켓 프로토콜을 사용한다.<br/>"
        "- 서버는 Win32 IOCP 기반 단일 실행 파일이며 9000 포트에서 최대 3000 세션을 수용한다.<br/>"
        "- 클라/서버 모두 동일한 PacketID 범위 규약을 공유한다 (0-99 시스템, 100-119 로비, "
        "120-149 인게임 동기화, 150-199 맵 이벤트, 500-599 클라이언트 요청).",
        style_body))
    flow.append(P("패킷 흐름", style_h2))
    flow.append(P(
        "클라이언트는 게임 스레드 → ClientNetworking::Send* → InboundCommandQueue → 워커 스레드 → 소켓 send 순서로 "
        "패킷을 보내고, 수신 시에는 워커가 RecvAndParsePackets에서 헤더 길이로 분리한 뒤 OutboundEventQueue에 적재하면 "
        "메인 스레드의 NetworkInstance::Tick → ClientNetworking::PumpEvents가 모두 꺼내 적절한 델리게이트를 호출한다. "
        "서버는 IOCP WorkerThread가 OnRecv 콜백에서 링버퍼에 누적한 후 PacketProcessor::Process로 디스패치한다.",
        style_body))
    flow.append(PageBreak())

    # ----- 클라이언트 -----
    flow.append(P("1. 클라이언트 코드", style_h1))
    flow.append(P(
        "경로: D:/Download/Claim_Of_Core_Project-MainClient/.../Claim_Of_Core/Source/Claim_Of_Core",
        style_note))
    for f in CLIENT_FILES:
        flow.extend(file_section(f['path'], f['summary'], f['items']))

    flow.append(PageBreak())

    # ----- 서버 -----
    flow.append(P("2. 서버 코드", style_h1))
    flow.append(P(
        "경로: D:/FinalProject/UnrealConnectServer_last/MainServer/MainServer",
        style_note))
    for f in SERVER_FILES:
        flow.extend(file_section(f['path'], f['summary'], f['items']))

    # ----- 부록 -----
    flow.append(PageBreak())
    flow.append(P("부록 A. 패킷 ID 범위 규약", style_h1))
    apx_rows = [
        ['ID 범위', '용도', '대표 패킷'],
        ['0 - 99', '시스템 / 글로벌', 'PKT_S2C_ACCESS_ALLOW, PKT_S2C_SNAPSHOT_NOTICE, PKT_S2C_SYNC_GAME_TIME_NOTICE'],
        ['100 - 119', '로비 (S2C)', 'PKT_S2C_LOGIN_OK/DENY, PKT_S2C_REGISTER_OK/DENY, PKT_S2C_ROOM_UPDATE, PKT_S2C_ROOM_ENTER, PKT_S2C_ROOM_INFO_BRD, PKT_S2C_GAME_START_BRD'],
        ['120 - 149', '인게임 동기화', 'PKT_S2C_DAMAGE_APPLY_BRD, PKT_S2C_STATUS_UPDATE_BRD, PKT_S2C_STATE_CHANGE_BRD, PKT_S2C_RESPAWN_BRD, PKT_S2C_ATTACK_ACTION_BRD, PKT_S2C_CHARACTER_SELECT_BRD'],
        ['150 - 199', '맵 이벤트', 'PKT_S2C_GAME_PHASE_CHANGE_BRD, PKT_S2C_MAPEVENT_TRIGGER_BRD, PKT_S2C_SPAWN_OBJECT_BRD'],
        ['500 - 519', '클라이언트 로비 요청', 'PKT_C2S_LOGIN_REQ, PKT_C2S_REGISTER_REQ, PKT_C2S_ROOM_CREATE_REQ, PKT_C2S_ROOM_JOIN_REQ, PKT_C2S_GAME_START_REQ, PKT_C2S_READY_REQ, PKT_C2S_CHARACTER_SELECT_REQ'],
        ['520 - 549', '클라이언트 키 입력', 'PKT_C2S_MOVE_KEYINPUT, PKT_C2S_JUMP_KEYINPUT'],
        ['550 - 599', '클라이언트 인게임 로직', 'PKT_C2S_ATTACK_KEYINPUT, PKT_C2S_ITEMPICKUP_KEYINPUT, PKT_C2S_ITEMDROP_KEYINPUT'],
    ]
    apx_tbl = Table(apx_rows, colWidths=[28 * mm, 38 * mm, 114 * mm], repeatRows=1)
    apx_tbl.setStyle(TableStyle([
        ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor('#1F3864')),
        ('TEXTCOLOR', (0, 0), (-1, 0), colors.white),
        ('FONTNAME', (0, 0), (-1, 0), 'MalgunBd'),
        ('FONTNAME', (0, 1), (-1, -1), 'Malgun'),
        ('FONTSIZE', (0, 0), (-1, -1), 9),
        ('ALIGN', (0, 0), (-1, 0), 'CENTER'),
        ('GRID', (0, 0), (-1, -1), 0.4, colors.HexColor('#888888')),
        ('VALIGN', (0, 0), (-1, -1), 'TOP'),
        ('LEFTPADDING', (0, 0), (-1, -1), 4),
        ('RIGHTPADDING', (0, 0), (-1, -1), 4),
        ('TOPPADDING', (0, 0), (-1, -1), 3),
        ('BOTTOMPADDING', (0, 0), (-1, -1), 3),
    ]))
    flow.append(apx_tbl)
    flow.append(Spacer(1, 8 * mm))

    flow.append(P("부록 B. 역할(Role) 스탯 요약", style_h1))
    role_rows = [
        ['Role', '코드', '이동속도 배수', 'MaxHP', '대표 스킬'],
        ['Striker', '0', '× 1.2', '100', '대시 (DashDuration=5s, DashSpeedMult=1.45)'],
        ['Guardian', '1', '× 0.8', '200', '단단해짐 (HardDuration=5s, HardScaleMult=1.25)'],
        ['Manipulator', '2', '× 1.0', '120', '점프 강화 (DBJPDuration=10s)'],
    ]
    role_tbl = Table(role_rows, colWidths=[28 * mm, 14 * mm, 28 * mm, 18 * mm, 92 * mm], repeatRows=1)
    role_tbl.setStyle(TableStyle([
        ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor('#1F3864')),
        ('TEXTCOLOR', (0, 0), (-1, 0), colors.white),
        ('FONTNAME', (0, 0), (-1, 0), 'MalgunBd'),
        ('FONTNAME', (0, 1), (-1, -1), 'Malgun'),
        ('FONTSIZE', (0, 0), (-1, -1), 9),
        ('ALIGN', (0, 0), (-1, 0), 'CENTER'),
        ('ALIGN', (1, 1), (3, -1), 'CENTER'),
        ('GRID', (0, 0), (-1, -1), 0.4, colors.HexColor('#888888')),
        ('VALIGN', (0, 0), (-1, -1), 'MIDDLE'),
    ]))
    flow.append(role_tbl)

    doc.build(flow)
    print("[OK] PDF 생성 완료:", OUTPUT_PATH)


if __name__ == '__main__':
    build()
