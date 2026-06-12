import html
import re
from pathlib import Path
from typing import List, Tuple, Dict

WORKSPACE = Path(r"D:\Download\Claim_Of_Core_Project-MainClient\Claim_Of_Core_Project-MainClient\MainClient_Codes\Claim_Of_Core")
CLIENT_ROOT = WORKSPACE / "Source" / "Claim_Of_Core"
SERVER_ROOT = Path(r"D:\FinalProject\UnrealConnectServer_last\MainServer\MainServer")
OUT_DIR = WORKSPACE / "Docs"
MD_PATH = OUT_DIR / "Claim_Of_Core_Code_Reference.md"
HTML_PATH = OUT_DIR / "Claim_Of_Core_Code_Reference.html"
HEADER_EXTS = {".h", ".hpp"}
SOURCE_EXTS = {".cpp", ".cc", ".cxx"}
SKIP_NAMES = {"GENERATED_BODY", "DECLARE_DYNAMIC_MULTICAST_DELEGATE"}


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="ignore")


def strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"//.*", "", text)
    return text


def normalize_space(text: str) -> str:
    return re.sub(r"\s+", " ", text).strip()


def split_camel(name: str) -> List[str]:
    parts = re.findall(r"[A-Z]+(?=[A-Z][a-z]|$)|[A-Z]?[a-z]+|\d+", name)
    return [p for p in parts if p]


def type_label(module: str) -> str:
    return "클라이언트" if module == "client" else "서버"


def file_purpose(path: Path, module: str) -> str:
    rel = path.relative_to(CLIENT_ROOT if module == "client" else SERVER_ROOT)
    parts = [p.lower() for p in rel.parts]
    name = path.stem.lower()

    if "networking" in parts:
        return "네트워크 연결, 패킷 전송/수신, 이벤트 분배를 담당하는 파일입니다."
    if "ui" in parts:
        return "로그인, 로비, 방, HUD 등 사용자 인터페이스 흐름을 담당하는 파일입니다."
    if "sub" in parts and "mycharacter" in name:
        return "플레이어 캐릭터의 입력, 상태, 역할, 전투, 네트워크 동기화 적용을 담당하는 핵심 파일입니다."
    if "gamestate" in parts:
        return "인게임 공용 상태와 라운드 흐름 표시를 담당하는 파일입니다."
    if "map" in parts:
        return "맵 기믹, 지형 오브젝트, 파괴/빙판/잔해 등 환경 상호작용을 담당하는 파일입니다."
    if "base" in parts:
        return "게임 모듈, 플레이어 컨트롤러 등 엔진 진입점과 기본 클래스를 담당하는 파일입니다."
    if module == "server":
        server_map = {
            "database": "DB 연결, 계정 조회/생성, 영속 데이터 접근을 담당하는 파일입니다.",
            "gamelogic": "서버 측 게임 규칙, 라운드 상태, 이동/전투/판정 계산을 담당하는 파일입니다.",
            "packet": "패킷 ID, 직렬화 포맷, 송수신 데이터 구조를 정의하는 파일입니다.",
            "packetprocessor": "수신 패킷을 해석하고 각 기능 처리기로 분배하는 파일입니다.",
            "roommanager": "방 생성/참가/시작/브로드캐스트와 룸 상태 관리를 담당하는 파일입니다.",
            "server": "IOCP 서버 초기화, 소켓 처리, 세션 생명주기를 담당하는 파일입니다.",
            "session": "클라이언트 세션 상태, 이동 의도, 게임 데이터 저장 구조를 정의하는 파일입니다.",
            "sessionmanager": "세션 컨테이너와 세션 등록/제거 정책을 담당하는 파일입니다.",
            "main": "서버 실행 진입점과 부트스트랩을 담당하는 파일입니다.",
            "logger": "서버 로그 출력 매크로와 기록 유틸리티를 제공합니다.",
        }
        return server_map.get(name, "서버 런타임 기능을 보조하는 파일입니다.")

    client_map = {
        "claim_of_core": "언리얼 모듈 초기화와 프로젝트 전역 설정 진입점을 담당하는 파일입니다.",
        "claim_of_coreplayercontroller": "플레이어 입력/마우스 모드와 클라이언트 제어 흐름을 담당하는 파일입니다.",
        "clientnetworktypes": "클라이언트에서 사용하는 패킷 구조체와 게임 동기화 데이터 형식을 정의합니다.",
        "networkinstance": "게임 인스턴스 기반 네트워크 세션, UI 흐름, 스냅샷 적용을 총괄하는 파일입니다.",
        "clientnetworking": "소켓 세션 객체를 감싸고 송수신 이벤트를 상위 로직에 전달하는 파일입니다.",
        "clientnetworkworker": "워커 스레드에서 패킷을 수신/해석하여 메인 스레드 이벤트로 넘기는 파일입니다.",
        "hpcomponent": "체력 관련 공통 계산과 상태 표시 보조를 담당하는 파일입니다.",
        "baseitem": "아이템 기본 동작과 줍기/버리기 상호작용 기반을 담당하는 파일입니다.",
    }
    return client_map.get(name, f"{type_label(module)} 측 {path.stem} 기능을 정의하는 파일입니다.")


def func_desc(name: str) -> str:
    if name.startswith("Init"):
        return "초기 상태를 구성하고 필요한 객체나 데이터를 준비합니다."
    if name.startswith("Shutdown"):
        return "종료 시점 정리와 리소스 해제를 수행합니다."
    if name.startswith("BeginPlay"):
        return "액터가 월드에 배치된 직후 실행되는 시작 로직입니다."
    if name.startswith("Tick"):
        return "매 프레임 또는 주기적으로 호출되어 상태를 갱신합니다."
    if name.startswith("Try"):
        return "조건을 확인한 뒤 요청 또는 동작을 시도합니다."
    if name.startswith("Show"):
        return "화면 요소 또는 UI를 생성/표시합니다."
    if name.startswith("Handle"):
        subject = " ".join(split_camel(name[6:])) or "event"
        return f"{subject} 관련 이벤트나 패킷을 받아 후속 처리를 수행합니다."
    if name.startswith("Request"):
        subject = " ".join(split_camel(name[7:])) or "request"
        return f"{subject} 요청 패킷 또는 서버 호출을 전송합니다."
    if name.startswith("Send"):
        subject = " ".join(split_camel(name[4:])) or "data"
        return f"{subject} 데이터를 네트워크나 다른 시스템으로 전달합니다."
    if name.startswith("Update"):
        subject = " ".join(split_camel(name[6:])) or "state"
        return f"{subject} 상태나 표시값을 최신 값으로 갱신합니다."
    if name.startswith("Apply"):
        subject = " ".join(split_camel(name[5:])) or "state"
        return f"{subject} 계산 결과를 컴포넌트나 현재 객체 상태에 반영합니다."
    if name.startswith("Set"):
        subject = " ".join(split_camel(name[3:])) or "value"
        return f"{subject} 값을 현재 객체에 설정합니다."
    if name.startswith("Get"):
        subject = " ".join(split_camel(name[3:])) or "value"
        return f"{subject} 값을 조회하여 반환합니다."
    if name.startswith("OnRep"):
        subject = " ".join(split_camel(name[5:])) or "replicated state"
        return f"{subject} 복제 값이 변경되었을 때 후속 동기화를 수행합니다."
    if name.startswith("Create"):
        subject = " ".join(split_camel(name[6:])) or "resource"
        return f"{subject} 객체 또는 리소스를 생성합니다."
    if name.startswith("Join"):
        subject = " ".join(split_camel(name[4:])) or "target"
        return f"{subject} 흐름에 참가하거나 연결을 수립합니다."
    if name.startswith("Find"):
        subject = " ".join(split_camel(name[4:])) or "target"
        return f"{subject} 객체를 검색해 반환합니다."
    if name.startswith("Ensure"):
        subject = " ".join(split_camel(name[6:])) or "target"
        return f"{subject} 객체가 없으면 생성하고, 있으면 재사용합니다."
    if name.startswith("Process"):
        return "입력 데이터를 해석하고 적절한 처리 흐름으로 연결합니다."
    return f"{' '.join(split_camel(name)) or name} 기능을 수행하는 함수입니다."


def var_desc(name: str, type_name: str) -> str:
    lname = name.lower()
    if "widgetclass" in lname:
        return "위젯 블루프린트 클래스를 지정하는 참조입니다."
    if "widgetinstance" in lname:
        return "런타임에 생성된 위젯 인스턴스를 가리킵니다."
    if "class" in name and "TSubclassOf" in type_name:
        return "런타임 생성에 사용할 클래스 참조입니다."
    if lname == "client":
        return "네트워크 세션/송수신을 담당하는 클라이언트 객체입니다."
    if "serveripaddress" in lname:
        return "접속 대상 서버 IP 문자열입니다."
    if "retry" in lname:
        return "재시도 횟수 또는 제한값을 저장합니다."
    if lname.startswith("b"):
        return "기능 토글 또는 현재 상태를 나타내는 불리언 플래그입니다."
    if "cached" in lname or "pending" in lname:
        return "즉시 처리하지 못한 값이나 최근 상태를 임시 저장합니다."
    if "currenthp" in lname or "maxhp" in lname:
        return "체력 관련 현재값/최대값을 저장합니다."
    if "role" in lname:
        return "역할 타입, 역할 텍스트, 역할 스킬 상태와 관련된 멤버입니다."
    if "camera" in lname:
        return "카메라 또는 카메라 보정 상태를 유지합니다."
    if "movement" in lname or "speed" in lname:
        return "이동 속도, 가속, 보간 등 이동 관련 상태를 유지합니다."
    if "map" in lname or "level" in lname:
        return "맵, 레벨, 라운드 흐름과 관련된 참조 또는 상태값입니다."
    if "room" in lname:
        return "방 상태, 방 UI, 방 참가자와 관련된 멤버입니다."
    if "uid" in lname or "session" in lname:
        return "세션/플레이어 식별자와 관련된 상태입니다."
    if "tmap" in type_name.lower():
        return "식별자와 런타임 객체를 매핑하는 컨테이너입니다."
    if "tarray" in type_name.lower() or "std::vector" in type_name.lower():
        return "동일한 종류의 데이터를 순서대로 저장하는 컨테이너입니다."
    return f"{name} 기능에 필요한 런타임 상태 또는 참조를 저장합니다."


def extract_header_members(text: str) -> Tuple[List[Dict], List[Dict], List[str]]:
    lines = text.splitlines()
    functions = []
    variables = []
    types = []
    class_depth = 0
    pending_macro = None

    for raw in lines:
        line = raw.strip()
        if not line:
            continue

        class_match = re.match(r"(UCLASS\(\))?\s*(class|struct)\s+([A-Za-z_][A-Za-z0-9_]*)", line)
        if class_match and line.endswith("{"):
            class_depth += 1
            types.append(class_match.group(3))

        if line.startswith(("UFUNCTION", "UPROPERTY")):
            pending_macro = line
            continue

        if line == "};" and class_depth > 0:
            class_depth -= 1
            continue

        if class_depth <= 0:
            continue

        if line.endswith(";") and "(" in line and ")" in line and not line.startswith(("if", "for", "while", "switch", "return")):
            sig = normalize_space(line[:-1])
            if sig and not any(skip in sig for skip in SKIP_NAMES):
                name_match = re.search(r"([~A-Za-z_][A-Za-z0-9_:<>]*)\s*\(", sig)
                if name_match:
                    name = name_match.group(1).split("::")[-1]
                    functions.append({"signature": sig, "name": name, "macro": pending_macro})
            pending_macro = None
            continue

        if line.endswith(";") and "(" not in line and not line.startswith(("public:", "private:", "protected:", "friend ", "typedef ", "using ", "enum ", "struct ", "class ")):
            var_line = normalize_space(line[:-1])
            if "=" in var_line:
                var_line = normalize_space(var_line.split("=", 1)[0])
            parts = var_line.rsplit(" ", 1)
            if len(parts) == 2:
                type_name, name = parts
                variables.append({"type": type_name, "name": name.strip(), "macro": pending_macro})
            pending_macro = None

    return functions, variables, types


def extract_cpp_functions(text: str) -> List[Dict]:
    clean = strip_comments(text)
    results = []
    pattern = re.compile(r"([A-Za-z_][A-Za-z0-9_:<>\*&\s~]+?)\s+([A-Za-z_][A-Za-z0-9_:~]*)\s*\(([^;{}]*)\)\s*\{", re.M)
    for match in pattern.finditer(clean):
        ret = normalize_space(match.group(1))
        full_name = match.group(2)
        params = normalize_space(match.group(3))
        name = full_name.split("::")[-1]
        if name in {"if", "for", "while", "switch"}:
            continue
        signature = f"{ret} {full_name}({params})".strip()
        results.append({"signature": signature, "name": name})
    return results


def merge_functions(header_funcs: List[Dict], cpp_funcs: List[Dict]) -> List[Dict]:
    seen = set()
    merged = []
    for item in header_funcs + cpp_funcs:
        key = item["signature"]
        if key in seen:
            continue
        seen.add(key)
        merged.append(item)
    return merged


def source_files(root: Path) -> List[Path]:
    return sorted([p for p in root.rglob("*") if p.suffix in HEADER_EXTS | SOURCE_EXTS])


def paired_files(root: Path) -> List[List[Path]]:
    by_stem = {}
    for path in source_files(root):
        rel_parent = path.parent.relative_to(root)
        by_stem.setdefault((rel_parent, path.stem), []).append(path)
    groups = []
    for _, items in sorted(by_stem.items(), key=lambda kv: str(kv[0][0] / kv[0][1])):
        groups.append(sorted(items, key=lambda p: p.suffix))
    return groups


def collect_group_info(paths: List[Path], module: str) -> Dict:
    header = next((p for p in paths if p.suffix in HEADER_EXTS), None)
    source = next((p for p in paths if p.suffix in SOURCE_EXTS), None)
    header_funcs = []
    variables = []
    types = []
    cpp_funcs = []
    if header:
        header_funcs, variables, types = extract_header_members(read_text(header))
    if source:
        cpp_funcs = extract_cpp_functions(read_text(source))
    funcs = merge_functions(header_funcs, cpp_funcs)
    anchor = header or source
    return {
        "module": module,
        "paths": paths,
        "anchor": anchor,
        "purpose": file_purpose(anchor, module),
        "types": types,
        "functions": funcs,
        "variables": variables,
    }


def escape_md(text: str) -> str:
    return text.replace("|", "\\|")


def build_markdown(groups: List[Dict]) -> str:
    lines = []
    lines.append("# Claim Of Core Client/Server Code Reference")
    lines.append("")
    lines.append("이 문서는 클라이언트와 서버 프로젝트의 주요 소스 파일을 기준으로, 프로젝트 내부에서 정의된 함수와 멤버 변수를 파일별로 정리한 참조 문서입니다.")
    lines.append("")
    lines.append("- 생성 기준: 프로젝트 소스 파일의 선언/정의 자동 추출 + 이름 기반 기능 설명")
    lines.append("- 용도: 이후 GPT에게 구조 설명, 수정 위치 질문, 네트워크 흐름 질문을 할 때 참조 자료로 사용")
    lines.append("- 주의: 일부 설명은 함수/변수명과 위치를 바탕으로 한 요약 설명이며, 엔진 내부 동작까지 완전히 대체하지는 않습니다.")
    lines.append("")

    client_groups = [g for g in groups if g["module"] == "client"]
    server_groups = [g for g in groups if g["module"] == "server"]

    lines.append("## 문서 구성")
    lines.append("")
    lines.append(f"- 클라이언트 파일 수: {len(client_groups)}")
    lines.append(f"- 서버 파일 수: {len(server_groups)}")
    lines.append(f"- 전체 파일 수: {len(groups)}")
    lines.append("")

    for section_name, section_groups in [("클라이언트", client_groups), ("서버", server_groups)]:
        lines.append(f"## {section_name}")
        lines.append("")
        for info in section_groups:
            rel = info["anchor"].relative_to(CLIENT_ROOT if info["module"] == "client" else SERVER_ROOT)
            lines.append(f"### {rel}")
            lines.append("")
            lines.append(f"- 절대 경로: `{info['anchor']}`")
            lines.append(f"- 파일 목적: {info['purpose']}")
            if info["types"]:
                lines.append(f"- 주요 타입: `{', '.join(info['types'])}`")
            lines.append(f"- 함수 수(추출): {len(info['functions'])}")
            lines.append(f"- 멤버 변수 수(추출): {len(info['variables'])}")
            lines.append("")

            if info["variables"]:
                lines.append("#### 멤버 변수")
                lines.append("")
                lines.append("| 이름 | 타입 | 설명 |")
                lines.append("| --- | --- | --- |")
                for var in info["variables"]:
                    lines.append(f"| `{escape_md(var['name'])}` | `{escape_md(var['type'])}` | {escape_md(var_desc(var['name'], var['type']))} |")
                lines.append("")

            if info["functions"]:
                lines.append("#### 함수")
                lines.append("")
                lines.append("| 이름 | 시그니처 | 설명 |")
                lines.append("| --- | --- | --- |")
                for func in info["functions"]:
                    lines.append(f"| `{escape_md(func['name'])}` | `{escape_md(func['signature'])}` | {escape_md(func_desc(func['name']))} |")
                lines.append("")

    return "\n".join(lines)


def md_to_html(md_text: str) -> str:
    html_lines = []
    in_table = False

    def close_table():
        nonlocal in_table
        if in_table:
            html_lines.append("</tbody></table>")
            in_table = False

    lines = md_text.splitlines()
    i = 0
    while i < len(lines):
        line = lines[i]
        if line.startswith("# "):
            close_table()
            html_lines.append(f"<h1>{html.escape(line[2:])}</h1>")
        elif line.startswith("## "):
            close_table()
            html_lines.append(f"<h2>{html.escape(line[3:])}</h2>")
        elif line.startswith("### "):
            close_table()
            html_lines.append(f"<h3>{html.escape(line[4:])}</h3>")
        elif line.startswith("#### "):
            close_table()
            html_lines.append(f"<h4>{html.escape(line[5:])}</h4>")
        elif line.startswith("- "):
            close_table()
            items = [html.escape(line[2:])]
            i += 1
            while i < len(lines) and lines[i].startswith("- "):
                items.append(html.escape(lines[i][2:]))
                i += 1
            html_lines.append("<ul>" + "".join(f"<li>{x}</li>" for x in items) + "</ul>")
            continue
        elif line.startswith("| ") and line.endswith(" |"):
            cells = [html.escape(c.strip().strip("`")) for c in line.strip("|").split("|")]
            if i + 1 < len(lines) and lines[i + 1].startswith("| ---"):
                close_table()
                html_lines.append("<table><thead><tr>" + "".join(f"<th>{c}</th>" for c in cells) + "</tr></thead><tbody>")
                in_table = True
                i += 2
                while i < len(lines) and lines[i].startswith("| ") and lines[i].endswith(" |"):
                    row_cells = [html.escape(c.strip().strip("`")) for c in lines[i].strip("|").split("|")]
                    html_lines.append("<tr>" + "".join(f"<td>{c}</td>" for c in row_cells) + "</tr>")
                    i += 1
                continue
        elif line.startswith("```"):
            close_table()
            code_lines = []
            i += 1
            while i < len(lines) and not lines[i].startswith("```"):
                code_lines.append(lines[i])
                i += 1
            html_lines.append(f"<pre><code>{html.escape(chr(10).join(code_lines))}</code></pre>")
        elif line.strip():
            close_table()
            text = re.sub(r"`([^`]+)`", lambda m: f"<code>{html.escape(m.group(1))}</code>", line)
            html_lines.append(f"<p>{text}</p>")
        else:
            close_table()
        i += 1

    close_table()
    body = "\n".join(html_lines)
    return f"""<!doctype html>
<html lang=\"ko\">
<head>
  <meta charset=\"utf-8\" />
  <title>Claim Of Core Code Reference</title>
  <style>
    body {{ font-family: 'Malgun Gothic', 'Segoe UI', sans-serif; margin: 28px; line-height: 1.45; color: #222; }}
    h1, h2, h3, h4 {{ color: #0f2d40; }}
    h1 {{ border-bottom: 2px solid #0f2d40; padding-bottom: 8px; }}
    h2 {{ margin-top: 28px; border-bottom: 1px solid #9bb7c7; padding-bottom: 4px; }}
    h3 {{ margin-top: 22px; background: #eef5f8; padding: 8px 10px; border-left: 4px solid #0f2d40; }}
    table {{ width: 100%; border-collapse: collapse; margin: 12px 0 18px; font-size: 11px; table-layout: fixed; }}
    th, td {{ border: 1px solid #c9d6de; padding: 6px 8px; vertical-align: top; word-wrap: break-word; }}
    th {{ background: #dfeef5; }}
    code {{ font-family: Consolas, 'Courier New', monospace; font-size: 0.95em; background: #f3f4f6; padding: 1px 3px; }}
    pre code {{ display: block; padding: 12px; white-space: pre-wrap; }}
    ul {{ margin-top: 4px; }}
    @page {{ size: A4; margin: 16mm; }}
  </style>
</head>
<body>
{body}
</body>
</html>"""


def main() -> None:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    groups = []
    for bundle in paired_files(CLIENT_ROOT):
        groups.append(collect_group_info(bundle, "client"))
    for bundle in paired_files(SERVER_ROOT):
        groups.append(collect_group_info(bundle, "server"))

    md_text = build_markdown(groups)
    html_text = md_to_html(md_text)
    MD_PATH.write_text(md_text, encoding="utf-8")
    HTML_PATH.write_text(html_text, encoding="utf-8")
    print(f"Generated: {MD_PATH}")
    print(f"Generated: {HTML_PATH}")


if __name__ == "__main__":
    main()
