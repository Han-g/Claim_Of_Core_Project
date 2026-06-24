from __future__ import annotations

import html
import os
import zipfile
from datetime import datetime


OUT = r"D:\FinalProject\docs\Claim_Of_Core_Portfolio_ClientSync_Revised.docx"

W = "http://schemas.openxmlformats.org/wordprocessingml/2006/main"
R = "http://schemas.openxmlformats.org/officeDocument/2006/relationships"


def esc(text: str) -> str:
    return html.escape(text, quote=False)


def xml_space(text: str) -> str:
    return ' xml:space="preserve"' if text.startswith(" ") or text.endswith(" ") else ""


def run(text: str, *, bold=False, italic=False, size=None, color=None) -> str:
    props = [
        '<w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/>'
    ]
    if bold:
        props.append("<w:b/>")
    if italic:
        props.append("<w:i/>")
    if color:
        props.append(f'<w:color w:val="{color}"/>')
    if size:
        props.append(f'<w:sz w:val="{int(size * 2)}"/>')
        props.append(f'<w:szCs w:val="{int(size * 2)}"/>')
    return f"<w:r><w:rPr>{''.join(props)}</w:rPr><w:t{xml_space(text)}>{esc(text)}</w:t></w:r>"


def para(
    text: str = "",
    *,
    style: str | None = None,
    bold=False,
    italic=False,
    size=None,
    color=None,
    before=None,
    after=None,
    line=None,
    align=None,
    num_id=None,
    ilvl=0,
    keep_next=False,
    runs: list[dict] | None = None,
) -> str:
    ppr = []
    if style:
        ppr.append(f'<w:pStyle w:val="{style}"/>')
    if num_id is not None:
        ppr.append(f'<w:numPr><w:ilvl w:val="{ilvl}"/><w:numId w:val="{num_id}"/></w:numPr>')
    if align:
        ppr.append(f'<w:jc w:val="{align}"/>')
    if keep_next:
        ppr.append("<w:keepNext/>")
    spacing = []
    if before is not None:
        spacing.append(f'w:before="{int(before * 20)}"')
    if after is not None:
        spacing.append(f'w:after="{int(after * 20)}"')
    if line is not None:
        spacing.append(f'w:line="{int(line * 240)}" w:lineRule="auto"')
    if spacing:
        ppr.append(f"<w:spacing {' '.join(spacing)}/>")

    if runs is None:
        text_xml = run(text, bold=bold, italic=italic, size=size, color=color)
    else:
        text_xml = "".join(
            run(
                part.get("text", ""),
                bold=part.get("bold", False),
                italic=part.get("italic", False),
                size=part.get("size"),
                color=part.get("color"),
            )
            for part in runs
        )

    return f"<w:p><w:pPr>{''.join(ppr)}</w:pPr>{text_xml}</w:p>"


def h1(text: str) -> str:
    return para(text, style="Heading1", keep_next=True)


def h2(text: str) -> str:
    return para(text, style="Heading2", keep_next=True)


def h3(text: str) -> str:
    return para(text, style="Heading3", keep_next=True)


def bullet(text: str) -> str:
    return para(text, num_id=1, after=6, line=1.167)


def numbered(text: str) -> str:
    return para(text, num_id=2, after=6, line=1.167)


def page_break() -> str:
    return '<w:p><w:r><w:br w:type="page"/></w:r></w:p>'


def cell(content: list[str], width: int, *, fill=None) -> str:
    shd = f'<w:shd w:fill="{fill}"/>' if fill else ""
    return (
        "<w:tc><w:tcPr>"
        f'<w:tcW w:w="{width}" w:type="dxa"/>'
        '<w:vAlign w:val="center"/>'
        "<w:tcMar>"
        '<w:top w:w="90" w:type="dxa"/><w:bottom w:w="90" w:type="dxa"/>'
        '<w:start w:w="120" w:type="dxa"/><w:end w:w="120" w:type="dxa"/>'
        "</w:tcMar>"
        f"{shd}"
        "</w:tcPr>"
        f"{''.join(content)}"
        "</w:tc>"
    )


def table(rows: list[list[list[str]]], widths: list[int], *, header=False) -> str:
    grid = "".join(f'<w:gridCol w:w="{w}"/>' for w in widths)
    trs = []
    for ridx, row in enumerate(rows):
        tr_pr = "<w:trPr><w:tblHeader/></w:trPr>" if header and ridx == 0 else ""
        tcs = []
        for cidx, content in enumerate(row):
            fill = "F2F4F7" if header and ridx == 0 else None
            tcs.append(cell(content, widths[cidx], fill=fill))
        trs.append(f"<w:tr>{tr_pr}{''.join(tcs)}</w:tr>")
    return (
        "<w:tbl>"
        "<w:tblPr>"
        '<w:tblW w:w="9360" w:type="dxa"/>'
        '<w:tblInd w:w="120" w:type="dxa"/>'
        '<w:tblLayout w:type="fixed"/>'
        '<w:tblCellMar><w:top w:w="90" w:type="dxa"/><w:bottom w:w="90" w:type="dxa"/>'
        '<w:start w:w="120" w:type="dxa"/><w:end w:w="120" w:type="dxa"/></w:tblCellMar>'
        '<w:tblBorders>'
        '<w:top w:val="single" w:sz="4" w:color="D0D7DE"/>'
        '<w:left w:val="single" w:sz="4" w:color="D0D7DE"/>'
        '<w:bottom w:val="single" w:sz="4" w:color="D0D7DE"/>'
        '<w:right w:val="single" w:sz="4" w:color="D0D7DE"/>'
        '<w:insideH w:val="single" w:sz="4" w:color="D0D7DE"/>'
        '<w:insideV w:val="single" w:sz="4" w:color="D0D7DE"/>'
        "</w:tblBorders>"
        "</w:tblPr>"
        f"<w:tblGrid>{grid}</w:tblGrid>"
        f"{''.join(trs)}"
        "</w:tbl>"
    )


def callout(title: str, body: str) -> str:
    return table(
        [[[para(title, bold=True, color="1F4D78", after=2), para(body, after=0)]]],
        [9360],
    )


def styles_xml() -> str:
    return f'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:styles xmlns:w="{W}">
  <w:docDefaults>
    <w:rPrDefault><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:sz w:val="22"/><w:szCs w:val="22"/></w:rPr></w:rPrDefault>
    <w:pPrDefault><w:pPr><w:spacing w:after="120" w:line="264" w:lineRule="auto"/></w:pPr></w:pPrDefault>
  </w:docDefaults>
  <w:style w:type="paragraph" w:default="1" w:styleId="Normal"><w:name w:val="Normal"/><w:qFormat/><w:pPr><w:spacing w:after="120" w:line="264" w:lineRule="auto"/></w:pPr><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:sz w:val="22"/></w:rPr></w:style>
  <w:style w:type="paragraph" w:styleId="Title"><w:name w:val="Title"/><w:basedOn w:val="Normal"/><w:qFormat/><w:pPr><w:spacing w:after="80"/></w:pPr><w:rPr><w:rFonts w:ascii="Calibri Light" w:hAnsi="Calibri Light" w:eastAsia="Malgun Gothic"/><w:sz w:val="50"/><w:color w:val="0B2545"/></w:rPr></w:style>
  <w:style w:type="paragraph" w:styleId="Subtitle"><w:name w:val="Subtitle"/><w:basedOn w:val="Normal"/><w:qFormat/><w:pPr><w:spacing w:after="240"/></w:pPr><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:sz w:val="27"/><w:color w:val="555555"/></w:rPr></w:style>
  <w:style w:type="paragraph" w:styleId="Heading1"><w:name w:val="heading 1"/><w:basedOn w:val="Normal"/><w:next w:val="Normal"/><w:qFormat/><w:pPr><w:keepNext/><w:spacing w:before="320" w:after="160"/></w:pPr><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:b/><w:sz w:val="32"/><w:color w:val="2E74B5"/></w:rPr></w:style>
  <w:style w:type="paragraph" w:styleId="Heading2"><w:name w:val="heading 2"/><w:basedOn w:val="Normal"/><w:next w:val="Normal"/><w:qFormat/><w:pPr><w:keepNext/><w:spacing w:before="240" w:after="120"/></w:pPr><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:b/><w:sz w:val="26"/><w:color w:val="2E74B5"/></w:rPr></w:style>
  <w:style w:type="paragraph" w:styleId="Heading3"><w:name w:val="heading 3"/><w:basedOn w:val="Normal"/><w:next w:val="Normal"/><w:qFormat/><w:pPr><w:keepNext/><w:spacing w:before="160" w:after="80"/></w:pPr><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:b/><w:sz w:val="24"/><w:color w:val="1F4D78"/></w:rPr></w:style>
</w:styles>'''


def numbering_xml() -> str:
    return f'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:numbering xmlns:w="{W}">
  <w:abstractNum w:abstractNumId="1"><w:multiLevelType w:val="singleLevel"/><w:lvl w:ilvl="0"><w:start w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText w:val="•"/><w:lvlJc w:val="left"/><w:pPr><w:tabs><w:tab w:val="num" w:pos="720"/></w:tabs><w:ind w:left="720" w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" w:eastAsia="Malgun Gothic"/></w:rPr></w:lvl></w:abstractNum>
  <w:num w:numId="1"><w:abstractNumId w:val="1"/></w:num>
  <w:abstractNum w:abstractNumId="2"><w:multiLevelType w:val="singleLevel"/><w:lvl w:ilvl="0"><w:start w:val="1"/><w:numFmt w:val="decimal"/><w:lvlText w:val="%1."/><w:lvlJc w:val="left"/><w:pPr><w:tabs><w:tab w:val="num" w:pos="720"/></w:tabs><w:ind w:left="720" w:hanging="360"/></w:pPr></w:lvl></w:abstractNum>
  <w:num w:numId="2"><w:abstractNumId w:val="2"/></w:num>
</w:numbering>'''


def header_xml() -> str:
    return f'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:hdr xmlns:w="{W}" xmlns:r="{R}">
  {para("Claim Of Core Portfolio | Client Sync Revision", size=9, color="666666", after=0)}
</w:hdr>'''


def footer_xml() -> str:
    return f'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:ftr xmlns:w="{W}" xmlns:r="{R}">
  <w:p><w:pPr><w:jc w:val="right"/><w:spacing w:after="0"/></w:pPr>
    {run("Page ", size=9, color="666666")}
    <w:r><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:sz w:val="18"/><w:color w:val="666666"/></w:rPr><w:fldChar w:fldCharType="begin"/></w:r>
    <w:r><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:sz w:val="18"/><w:color w:val="666666"/></w:rPr><w:instrText xml:space="preserve"> PAGE </w:instrText></w:r>
    <w:r><w:rPr><w:rFonts w:ascii="Calibri" w:hAnsi="Calibri" w:eastAsia="Malgun Gothic"/><w:sz w:val="18"/><w:color w:val="666666"/></w:rPr><w:fldChar w:fldCharType="end"/></w:r>
  </w:p>
</w:ftr>'''


def body_xml() -> str:
    today = datetime.now().strftime("%Y.%m.%d")
    b: list[str] = []

    b.append(para("PORTFOLIO DRAFT", size=11, bold=True, color="2E74B5", after=4))
    b.append(para("Claim Of Core", style="Title"))
    b.append(para("서버-클라이언트 동기화 문제 해결 중심 포트폴리오", style="Subtitle"))
    b.append(
        table(
            [
                [[para("지원 대상", bold=True, after=0)], [para("Conworth / [지원 직무 입력]", after=0)]],
                [[para("작성자", bold=True, after=0)], [para("[이름] / [학교] / [전공]", after=0)]],
                [[para("핵심 메시지", bold=True, after=0)], [para("클라이언트 흐름을 이해하지 못해 생긴 동기화 문제를 함수 단위로 추적하고, 서버-클라이언트 패킷 흐름을 맞춰간 경험", after=0)]],
                [[para("작성일", bold=True, after=0)], [para(today, after=0)]],
            ],
            [1800, 7560],
        )
    )
    b.append(para("", after=4))
    b.append(callout(
        "이 포트폴리오에서 보여줄 것",
        "단순히 IOCP 서버를 만들었다는 설명보다, 서버 개발자가 클라이언트의 요청 함수와 이벤트 반영 흐름을 이해해야 실제 동기화 문제를 해결할 수 있다는 점을 보여줍니다. `ClientNetworking`, `FClientNetworkWorker`, `UNetworkInstance`, `PacketProcessor`, `GameLogic`을 연결해 기능별 흐름을 정리했습니다.",
    ))

    b.append(h1("1. 개요"))
    b.append(para("Claim Of Core는 Unreal Engine 클라이언트와 C++ Windows API IOCP 서버를 연동한 멀티플레이 액션 게임 프로젝트입니다. 서버는 접속, 패킷, 룸, 게임 판정을 담당하고, 클라이언트는 입력 송신, UI 전환, 캐릭터와 맵 오브젝트 반영을 담당합니다."))
    b.append(para("초기에는 서버 구현에 집중해 `PacketProcessor`와 `GameLogic`을 먼저 만들었지만, 클라이언트에서 어떤 함수가 실제 패킷을 보내고 어떤 함수가 서버 결과를 게임 화면에 반영하는지 제대로 이해하지 못해 동기화 문제가 발생했습니다. 이후 Google Docs의 Server Client FlowChart처럼 흐름을 함수 단위로 정리하면서, 서버 핸들러와 클라이언트 요청/수신 경로를 맞추는 방식으로 문제를 추적했습니다."))
    b.append(bullet("서버 핵심: `IOCPServer`, `SessionManager`, `RoomManager`, `PacketProcessor`, `GameLogic`"))
    b.append(bullet("클라이언트 핵심: `ClientNetworking`, `FClientNetworkWorker`, `UNetworkInstance`, `AMyCharacter`"))
    b.append(bullet("동기화 기준: `PacketID`, `PacketHeader`, `GameData`, 패킷별 request/handler/broadcast/handle 함수 연결"))

    b.append(h1("2. 경험한 문제"))
    b.append(h2("2.1 문제 상황"))
    b.append(para("서버에는 `PacketProcessor::InitHandler`로 여러 패킷 핸들러가 등록되어 있었지만, 클라이언트에서 실제로 해당 패킷을 보내는 함수가 무엇인지 확인하지 않으면 서버 로직은 실행되지 않았습니다. 반대로 서버가 결과 패킷을 브로드캐스트해도, 클라이언트의 `FClientNetworkWorker::HandlePacket`과 `ClientNetworking::PumpEvents`, `UNetworkInstance` 핸들러 연결이 맞지 않으면 화면에는 변화가 나타나지 않았습니다."))
    b.append(bullet("예: 이동은 `AMyCharacter` Tick에서 `UNetworkInstance::SendMoveInputToServer`를 호출해야 `PKT_C2S_MOVE_KEYINPUT`이 서버에 도달합니다."))
    b.append(bullet("예: 서버 스냅샷은 `PKT_S2C_SNAPSHOT_NOTICE`로 오지만, `UNetworkInstance::HandleSnapshotReceived`에서 원격 캐릭터를 찾거나 생성해야 화면에 반영됩니다."))
    b.append(bullet("예: 공격은 서버에 `Handle_Attack_KeyInput`이 있어도 클라이언트의 `RequestAttackInput` 경로와 실제 `EnqueueSendCommand` 연결을 함께 확인해야 합니다."))
    b.append(h2("2.2 원인"))
    b.append(para("원인은 서버 관점에서만 기능을 바라본 것이었습니다. 서버 함수가 준비되어 있으면 기능이 동작한다고 생각했지만, 실제 흐름은 클라이언트 요청 함수, 네트워크 worker thread, 서버 패킷 핸들러, 서버 브로드캐스트, 클라이언트 이벤트 처리 함수가 모두 연결되어야 완성됩니다."))
    b.append(h2("2.3 해결 방식"))
    b.append(numbered("각 기능마다 `클라이언트 요청 함수 -> PacketID -> 서버 핸들러 -> GameLogic 처리 -> 서버 송신 패킷 -> 클라이언트 반영 함수` 순서로 표를 만들었습니다."))
    b.append(numbered("서버에서 먼저 의심하지 않고, 클라이언트가 실제로 `ClientNetworking::EnqueueSendCommand`까지 도달하는지 확인했습니다."))
    b.append(numbered("서버 브로드캐스트 후에는 `FClientNetworkWorker::HandlePacket`에서 이벤트가 만들어지고 `ClientNetworking::PumpEvents`를 통해 게임 스레드의 `UNetworkInstance` 핸들러가 호출되는지 확인했습니다."))
    b.append(numbered("결과적으로 이동, 룸, 캐릭터 선택, 맵 이벤트처럼 성공한 흐름과 공격 입력처럼 연결을 더 점검해야 하는 흐름을 구분할 수 있게 되었습니다."))

    b.append(page_break())
    b.append(h1("3. 클라이언트 구현 정리"))
    b.append(para("기존 포트폴리오에는 서버 설명이 많았기 때문에, 수정본에서는 클라이언트의 기본 구조와 실제 함수 흐름을 함께 넣었습니다."))
    b.append(h2("3.1 시작과 delegate 연결"))
    b.append(bullet("`UNetworkInstance::Init`에서 `Client = MakeShared<ClientNetworking>()`로 네트워크 객체를 생성합니다."))
    b.append(bullet("`Client->OnConnected`, `OnLoginResult`, `OnRoomListUpdated`, `OnSnapshotReceived`, `OnMapEventTriggered` 등의 delegate를 `UNetworkInstance` 핸들러에 연결합니다."))
    b.append(bullet("`Client->Start(ServerIPAddress, 9000)`이 호출되면 `ClientNetworking::Start`가 `FClientNetworkWorker`를 만들고 `RequestConnect`를 큐에 넣습니다."))
    b.append(h2("3.2 worker thread와 game thread 분리"))
    b.append(bullet("`FClientNetworkWorker::Run`은 네트워크 worker thread에서 `FlushInboundCommands`, `RecvAndParsePackets`, `HandleReconnect`를 반복합니다."))
    b.append(bullet("`FlushInboundCommands`는 CONNECT, DISCONNECT, SEND 명령을 처리하고, SEND는 `SendRawPacket`으로 서버에 전송합니다."))
    b.append(bullet("`RecvAndParsePackets`는 socket buffer에서 `FPacketHeader`와 payload를 조립하고 `HandlePacket`으로 넘깁니다."))
    b.append(bullet("`HandlePacket`은 서버 패킷을 `FNetEvent`로 변환해 `OutboundEventQueue`에 넣습니다."))
    b.append(bullet("`UNetworkInstance::Tick`은 매 프레임 `Client->PumpEvents()`를 호출해 이벤트를 게임 스레드에서 처리합니다."))
    b.append(h2("3.3 클라이언트 요청 함수"))
    b.append(
        table(
            [
                [[para("기능", bold=True, after=0)], [para("클라이언트 함수", bold=True, after=0)], [para("전송 패킷", bold=True, after=0)]],
                [[para("로그인", after=0)], [para("`UNetworkInstance::TryLogin` -> `ClientNetworking::LoginAccess`", after=0)], [para("`PKT_C2S_LOGIN_REQ`", after=0)]],
                [[para("방 생성/입장", after=0)], [para("`CreateRoom`, `JoinRoom` -> `CreateRoomRequest`, `JoinRoomRequest`", after=0)], [para("`PKT_C2S_ROOM_CREATE_REQ`, `PKT_C2S_ROOM_JOIN_REQ`", after=0)]],
                [[para("캐릭터/Ready", after=0)], [para("`SelectCharacterAndReady`, `RequestReady` -> `CharacterSelectRequest`, `ReadyToggleRequest`", after=0)], [para("`PKT_C2S_CHARACTER_SELECT_REQ`, `PKT_C2S_READY_REQ`", after=0)]],
                [[para("게임 시작", after=0)], [para("`RequestGameStart` -> `GameStartRequest`", after=0)], [para("`PKT_C2S_GAME_START_REQ`", after=0)]],
                [[para("이동/점프", after=0)], [para("`SendMoveInputToServer`, `RequestJumpInput` -> `SendMoveInput`, `SendJumpInput`", after=0)], [para("`PKT_C2S_MOVE_KEYINPUT`, `PKT_C2S_JUMP_KEYINPUT`", after=0)]],
                [[para("아이템/오브젝트", after=0)], [para("`RequestItemPickup`, `RequestItemDrop`, `RequestObjectHit`", after=0)], [para("`PKT_C2S_ITEMPICKUP_KEYINPUT`, `PKT_C2S_ITEMDROP_KEYINPUT`, `PKT_C2S_OBJECT_HIT_REQ`", after=0)]],
                [[para("맵 특수 기능", after=0)], [para("`RequestIceFloorStanding`, `RequestGrenadeBlackHoleSpawn`", after=0)], [para("`PKT_C2S_ICE_FLOOR_STAND_REQ`, `PKT_C2S_GRENADE_BLACKHOLE_REQ`", after=0)]],
            ],
            [1500, 5160, 2700],
            header=True,
        )
    )

    b.append(h1("4. 서버 구현 정리"))
    b.append(para("서버는 IOCP 기반 비동기 입출력과 룸 단위 게임 루프를 중심으로 구성했습니다. 포트폴리오에서는 모든 코드를 설명하기보다, 클라이언트와 맞물리는 지점 위주로 소개합니다."))
    b.append(bullet("부트스트랩: `main` -> `IOCPServer::InitLogger` -> `IOCPServer::Init` -> `IOCPServer::Start` -> `GameFrameProtocol`"))
    b.append(bullet("접속: `AcceptThread` -> `SessionManager::AcceptNewClient` -> `IOCPServer::OnConnect` -> `PKT_S2C_ACCESS_ALLOW`"))
    b.append(bullet("수신: `WorkerThread` -> `OnRecv` -> `RingBufPeek`/`RingBufpop` -> `PacketProcess` -> `PacketProcessor::Process`"))
    b.append(bullet("송신: `SendPacket` -> session send queue -> `SendProtocol` -> `WSASend` -> `OnSend`"))
    b.append(bullet("게임 루프: `GameFrameProtocol` -> `RoomManager::UpdateRooms` -> `Room::UpdateGameLogic` -> `GameLogic::Update` -> `Room::BroadcastGameDatas`"))
    b.append(bullet("판정: `UpdatePlayerMovement`, `HandleAttackInput`, `ApplyDamage`, `HandleItemPickup`, `UpdateIceCaveMap`, `UpdateSpaceStation`"))

    b.append(page_break())
    b.append(h1("5. 기능별 함수 흐름"))
    b.append(para("이 표는 Google Docs의 Server Client FlowChart 내용을 포트폴리오용으로 줄인 것입니다. 면접에서는 이 표를 기준으로 특정 기능 하나를 골라 흐름을 설명하면 됩니다."))
    b.append(
        table(
            [
                [[para("기능", bold=True, after=0)], [para("함수 흐름", bold=True, after=0)], [para("동기화 포인트", bold=True, after=0)]],
                [[para("로그인", after=0)], [para("`TryLogin` -> `LoginAccess` -> `PKT_C2S_LOGIN_REQ` -> `Handle_LoginReq` -> `DBWorkerThread` -> `PKT_S2C_LOGIN_OK` -> `HandleLoginResult`", after=0)], [para("DB 작업은 별도 thread에서 처리하고, 결과만 게임 클라이언트에 전달", after=0)]],
                [[para("방 입장", after=0)], [para("`JoinRoom` -> `JoinRoomRequest` -> `Handle_Room_JoinReq` -> `RoomManager::JoinRoom` -> `PKT_S2C_ROOM_ENTER` / `PKT_S2C_ROOM_INFO_BRD` -> `HandleRoomEnterResult`", after=0)], [para("본인 결과와 기존 멤버 갱신을 분리해 UI 상태를 맞춤", after=0)]],
                [[para("게임 시작", after=0)], [para("`RequestGameStart` -> `GameStartRequest` -> `Handle_Game_StartReq` -> `RoomManager::GameStart` -> `Room::InitGameLogic` -> `PKT_S2C_MAP_SELECT_NOTICE` / `PKT_S2C_GAME_START_BRD`", after=0)], [para("서버가 맵과 초기 캐릭터 데이터를 결정하고 클라이언트는 로딩과 UI 전환 수행", after=0)]],
                [[para("이동", after=0)], [para("`AMyCharacter` Tick -> `SendMoveInputToServer` -> `SendMoveInput` -> `PKT_C2S_MOVE_KEYINPUT` -> `Handle_Move_KeyInput` -> `UpdatePlayerMovement` -> `PKT_S2C_SNAPSHOT_NOTICE` -> `HandleSnapshotReceived`", after=0)], [para("클라이언트는 입력을 보내고, 실제 위치는 서버 스냅샷으로 동기화", after=0)]],
                [[para("공격/피해", after=0)], [para("`RequestAttackInput` -> `SendGameplayAttackPacket` -> `TestFuncInput` -> `PKT_C2S_ATTACK_KEYINPUT` -> `Handle_Attack_KeyInput` -> `GameLogic::HandleAttackInput` -> `BroadcastAttackAction` / `BroadcastDamageApply`", after=0)], [para("서버 핸들러만으로는 부족하며, 클라이언트 요청 함수가 실제 송신까지 연결되어야 함", after=0)]],
                [[para("아이템", after=0)], [para("`RequestItemPickup` -> `ItemPickupRequest` -> `Handle_ItemPickup_KeyInput` -> `GameLogic::HandleItemPickup` -> `PKT_S2C_ITEM_OWNERSHIP_BRD` -> `HandleItemOwnershipChanged`", after=0)], [para("소유권은 서버에서 결정하고 클라이언트는 결과만 반영", after=0)]],
                [[para("Ice Cave", after=0)], [para("`UpdateIceCaveMap` -> `SpawnIceChillZone` / `ApplyFreezeToPlayer` -> `PKT_S2C_MAPEVENT_TRIGGER_BRD` / `PKT_S2C_STATUS_EFFECT_BRD` -> `HandleMapEventTriggered` / `HandleStatusEffect`", after=0)], [para("맵 위험요소와 상태이상을 서버 기준으로 맞춤", after=0)]],
                [[para("Space Station", after=0)], [para("`RequestGrenadeBlackHoleSpawn` -> `GrenadeBlackHoleRequest` -> `Handle_Grenade_SpawnReq` -> `HandleGrenadeBlackHoleSpawn` -> `AddSpaceBlackHole` / `ApplyBlackHolePull` -> `ABlackHoleActor` 반영", after=0)], [para("시각 효과는 클라이언트, 힘 적용은 서버에서 관리", after=0)]],
            ],
            [1300, 5660, 2400],
            header=True,
        )
    )

    b.append(h1("6. 대표 문제 해결 사례"))
    b.append(h2("사례: 서버 핸들러와 클라이언트 함수 흐름 불일치"))
    b.append(para("초기에는 서버의 `PacketProcessor::InitHandler`에 핸들러를 등록하고 `GameLogic`에 판정 함수를 구현하면 기능이 동작한다고 생각했습니다. 하지만 실제로는 클라이언트의 버튼, 캐릭터 Tick, UI 함수가 `ClientNetworking::EnqueueSendCommand`까지 도달해야 서버가 해당 패킷을 받을 수 있었습니다. 또한 서버가 결과를 보내도 클라이언트의 worker thread가 이벤트로 변환하고, game thread에서 `UNetworkInstance` 핸들러가 호출되어야 화면에 반영됩니다."))
    b.append(h3("확인한 흐름"))
    b.append(numbered("클라이언트 요청 지점: `UNetworkInstance::Request...` 또는 `AMyCharacter` Tick"))
    b.append(numbered("전송 지점: `ClientNetworking::EnqueueSendCommand`와 `FClientNetworkWorker::SendRawPacket`"))
    b.append(numbered("서버 수신 지점: `IOCPServer::OnRecv`와 `PacketProcessor::Process`"))
    b.append(numbered("서버 판정 지점: `GameLogic`의 기능별 함수"))
    b.append(numbered("클라이언트 반영 지점: `FClientNetworkWorker::HandlePacket` -> `ClientNetworking::PumpEvents` -> `UNetworkInstance::Handle...`"))
    b.append(h3("얻은 결과"))
    b.append(para("이 과정을 통해 동기화 문제를 서버 코드만 보고 판단하지 않게 되었습니다. 특정 기능이 동작하지 않을 때 `패킷이 안 나갔는지`, `서버가 못 받았는지`, `서버 결과가 안 나갔는지`, `클라이언트가 받아도 game thread에서 반영하지 못했는지`를 단계별로 분리해서 확인할 수 있게 되었습니다."))
    b.append(callout(
        "면접에서 강조할 문장",
        "이 프로젝트에서 가장 크게 배운 점은 서버 개발도 클라이언트 흐름을 알아야 한다는 것입니다. 서버 권위 구조를 만들기 위해서는 서버 판정 함수뿐 아니라, 클라이언트 요청 함수와 수신 반영 함수까지 함께 이해해야 실제 동기화 문제를 해결할 수 있었습니다.",
    ))

    b.append(page_break())
    b.append(h1("7. 전공 지식과 연결"))
    b.append(para("클라이언트 이해를 확장하는 과정에서 학교 수업의 그래픽스, 카메라, 물리 개념도 프로젝트 설명에 연결할 수 있습니다."))
    b.append(
        table(
            [
                [[para("수업/경험", bold=True, after=0)], [para("프로젝트와 연결", bold=True, after=0)]],
                [[para("카메라 calibration", after=0)], [para("카메라 방향과 좌표계 이해를 바탕으로 `MoveIntent::CameraDir`가 서버 이동 계산에서 어떤 의미를 갖는지 이해했습니다. 클라이언트 입력은 카메라 기준 방향으로 생성되고, 서버는 이를 `UpdatePlayerMovement`에서 위치 변화로 변환합니다.", after=0)]],
                [[para("물리 기반 파티클", after=0)], [para("중력, 힘, 충돌, 감쇠 개념은 `ALargeDebrisActor`의 낙하/파편 효과, `ABlackHoleActor`의 흡입 표현, Niagara 효과를 설명하는 배경이 되었습니다.", after=0)]],
                [[para("운영체제/네트워크", after=0)], [para("스레드, 큐, 비동기 I/O 개념은 `FClientNetworkWorker`의 worker thread와 `IOCPServer`의 IOCP worker thread 구조를 이해하는 데 연결되었습니다.", after=0)]],
            ],
            [2200, 7160],
            header=True,
        )
    )

    b.append(h1("8. 보강할 자료"))
    b.append(bullet("스크린샷 1: 서버 콘솔에서 `AcceptThread`, 로그인, 룸 입장 로그가 보이는 화면"))
    b.append(bullet("스크린샷 2: Unreal 클라이언트에서 룸 입장/Ready/게임 시작 UI가 바뀌는 화면"))
    b.append(bullet("스크린샷 3: `PKT_S2C_SNAPSHOT_NOTICE`로 원격 캐릭터가 동기화되는 장면"))
    b.append(bullet("스크린샷 4: Ice Cave 또는 Space Station 맵 이벤트가 서버 기준으로 동기화되는 장면"))
    b.append(bullet("코드 캡처: `FClientNetworkWorker::RecvAndParsePackets`, `ClientNetworking::PumpEvents`, `PacketProcessor::InitHandler`, `GameLogic::UpdatePlayerMovement`"))

    b.append(h1("9. 자기소개서용 짧은 정리"))
    b.append(para("저는 C++ Windows API IOCP 서버를 구현하며 Unreal Engine 클라이언트와의 실시간 동기화 흐름을 경험했습니다. 초기에는 서버 함수 구현에 집중해 클라이언트 요청 함수와 이벤트 반영 흐름을 충분히 이해하지 못했고, 그 결과 서버 핸들러가 있어도 실제 기능이 화면에 반영되지 않는 문제를 겪었습니다. 이후 `UNetworkInstance`, `ClientNetworking`, `FClientNetworkWorker`, `PacketProcessor`, `GameLogic`의 연결을 기능별로 추적하며, 패킷 송신부터 서버 판정, 클라이언트 반영까지의 흐름을 정리했습니다. 이 경험을 통해 서버 개발에서도 클라이언트 구조를 이해해야 안정적인 동기화와 문제 해결이 가능하다는 것을 배웠습니다."))

    sect = (
        '<w:sectPr>'
        '<w:headerReference w:type="default" r:id="rId5"/>'
        '<w:footerReference w:type="default" r:id="rId6"/>'
        '<w:pgSz w:w="12240" w:h="15840"/>'
        '<w:pgMar w:top="1440" w:right="1440" w:bottom="1440" w:left="1440" w:header="709" w:footer="709" w:gutter="0"/>'
        '<w:cols w:space="720"/>'
        '<w:docGrid w:linePitch="360"/>'
        '</w:sectPr>'
    )
    return "".join(b) + sect


def document_xml() -> str:
    return f'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:document xmlns:w="{W}" xmlns:r="{R}">
  <w:body>{body_xml()}</w:body>
</w:document>'''


CONTENT_TYPES = '''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
  <Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/>
  <Default Extension="xml" ContentType="application/xml"/>
  <Override PartName="/word/document.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml"/>
  <Override PartName="/word/styles.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml"/>
  <Override PartName="/word/numbering.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml"/>
  <Override PartName="/word/settings.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.settings+xml"/>
  <Override PartName="/word/header1.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.header+xml"/>
  <Override PartName="/word/footer1.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.footer+xml"/>
  <Override PartName="/docProps/core.xml" ContentType="application/vnd.openxmlformats-package.core-properties+xml"/>
  <Override PartName="/docProps/app.xml" ContentType="application/vnd.openxmlformats-officedocument.extended-properties+xml"/>
</Types>'''


ROOT_RELS = '''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
  <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument" Target="word/document.xml"/>
  <Relationship Id="rId2" Type="http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties" Target="docProps/core.xml"/>
  <Relationship Id="rId3" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties" Target="docProps/app.xml"/>
</Relationships>'''


DOC_RELS = '''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
  <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles" Target="styles.xml"/>
  <Relationship Id="rId2" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/numbering" Target="numbering.xml"/>
  <Relationship Id="rId3" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/settings" Target="settings.xml"/>
  <Relationship Id="rId5" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/header" Target="header1.xml"/>
  <Relationship Id="rId6" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/footer" Target="footer1.xml"/>
</Relationships>'''


SETTINGS = f'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:settings xmlns:w="{W}">
  <w:zoom w:percent="100"/>
  <w:defaultTabStop w:val="720"/>
  <w:characterSpacingControl w:val="doNotCompress"/>
</w:settings>'''


CORE = '''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<cp:coreProperties xmlns:cp="http://schemas.openxmlformats.org/package/2006/metadata/core-properties" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:dcmitype="http://purl.org/dc/dcmitype/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
  <dc:title>Claim Of Core Client Sync Portfolio</dc:title>
  <dc:subject>Server-client synchronization portfolio draft</dc:subject>
  <dc:creator>Codex</dc:creator>
  <cp:lastModifiedBy>Codex</cp:lastModifiedBy>
</cp:coreProperties>'''


APP = '''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/extended-properties" xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
  <Application>Codex</Application>
  <DocSecurity>0</DocSecurity>
  <ScaleCrop>false</ScaleCrop>
  <Company></Company>
  <LinksUpToDate>false</LinksUpToDate>
  <SharedDoc>false</SharedDoc>
  <HyperlinksChanged>false</HyperlinksChanged>
  <AppVersion>16.0000</AppVersion>
</Properties>'''


def main() -> None:
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    files = {
        "[Content_Types].xml": CONTENT_TYPES,
        "_rels/.rels": ROOT_RELS,
        "word/document.xml": document_xml(),
        "word/_rels/document.xml.rels": DOC_RELS,
        "word/styles.xml": styles_xml(),
        "word/numbering.xml": numbering_xml(),
        "word/settings.xml": SETTINGS,
        "word/header1.xml": header_xml(),
        "word/footer1.xml": footer_xml(),
        "docProps/core.xml": CORE,
        "docProps/app.xml": APP,
    }
    with zipfile.ZipFile(OUT, "w", compression=zipfile.ZIP_DEFLATED) as zf:
        for name, content in files.items():
            zf.writestr(name, content.encode("utf-8"))
    print(OUT)


if __name__ == "__main__":
    main()
