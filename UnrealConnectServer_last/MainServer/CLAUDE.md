# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

This is a Visual Studio 2022 solution (`MainServer.sln`) targeting Windows x64, using MSVC v143 toolset.

**Build from CLI (MSBuild):**
```
msbuild MainServer.sln /p:Configuration=Debug /p:Platform=x64
msbuild MainServer.sln /p:Configuration=Release /p:Platform=x64
```

Output binary: `x64\Debug\MainServer.exe` or `x64\Release\MainServer.exe`

**Run:**
```
x64\Debug\MainServer.exe
```
The server reads `server_config.ini` (in the working directory) for the DB connection string. Copy `MainServer\server_config.ini.example` to `server_config.ini` and adjust before first run.

## Architecture

An IOCP-based Windows game server designed to communicate with Unreal Engine clients. It listens on TCP port 9000, supports up to 3000 concurrent sessions, and runs a ~60 FPS game loop.

### Thread Model
- **Accept thread** (`AcceptThread`): Accepts new TCP connections.
- **IOCP worker threads** (`WorkerThread`, ×4): Handle `GetQueuedCompletionStatus` completions — `RECV`, `SEND`, and `AWAIT` operations.
- **DB worker thread** (`DBWorkerThread`): Consumes a `std::queue<DBData>` for async login/register operations; signalled via `std::condition_variable`.
- **Main thread**: Drives the game loop at ~16ms intervals via `server.GameFrameProtocol()`.

### Core Classes

| Class | File | Role |
|---|---|---|
| `IOCPServer` | `server.h/cpp` | Top-level orchestrator. Owns IOCP handle, listen socket, all managers, and packet dispatch. |
| `Session` | `session.h` | Per-client state: socket, playerUID, sessionID, roomID, ring buffer for recv (`s_ringbuf`), `sendQueue`, and `ESessionState`. |
| `SessionManager` | `SessionManager.h/cpp` | Singleton pool of up to 3000 `Session*`. Assigns/reclaims session slots via `m_FreeSessionQueue`. |
| `PacketProcessor` | `PacketProcessor.h/cpp` | Singleton dispatch table (`unordered_map<int, HandlerFunc>`). `InitHandler()` registers all packet handlers; `Process()` routes by `packetID`. |
| `RoomManager` | `RoomManager.h/cpp` | Singleton managing up to 500 `Room` objects. Handles create/join/leave/destroy. |
| `Room` | `RoomManager.h` | Contains a `vector<Session*>` of members (max 6), a `GameLogic*`, and `ERoomState` (WAITING/PLAYING/FINISHED). |
| `GameLogic` | `GameLogic.h/cpp` | In-room game state: HP, combat, items, map events (Building & IceCave maps), round phases. |
| `DBHelper` | `Database.h/cpp` | Singleton ODBC wrapper for SQL Server Express. Handles `CheckLogin` and `CreateAccount` with input validation to prevent SQL injection. |

### Packet Protocol

All packets use a 4-byte header (`PacketHeader`): `uint16 packet_size` + `uint16 packet_ID`.

`PacketReader` (in `Packet.h`) is a template-based deserializer. It handles Unreal `FString` wire format: positive length = ANSI, negative length = UTF-16LE.

**PacketID ranges** (see `Packet.h`):
- `0–99`: High-frequency system sync (snapshot, timer)
- `100–199`: S2C — lobby, room, in-game broadcast
- `500–599`: C2S — lobby requests, key inputs
- `1000+`: Error codes

### Session State Machine
```
LOGIN → LOBBY → ROOM → INGAME
```
State transitions are driven by packet handlers in `PacketProcessor`.

### Database
Connection string is read from `server_config.ini` (`[Database]` section). Uses ODBC (`odbc32.lib`) connecting to a local SQL Server Express instance (`ClaimOfCore` database). DB operations are offloaded to the DB worker thread via `PushDBTask()`.

### Logging
Macros defined in `logger.h` (wraps `logging.hpp`):
```cpp
LOG_INFO("format %s", arg);
LOG_WARN("...");
LOG_ERROR("...");
```
Output goes to `ServerLog.txt` with timestamps.

## Key Constants
- Max sessions: `MAXCLIENT = 3000` (`SessionManager.h`)
- Max rooms: `MaxRoom = 500` (`RoomManager.h`)
- Max players per room: `MaxMember = 6` (`RoomManager.h`)
- Recv ring buffer size: `BUF_SIZE = 10240` bytes (`session.h`)
- Server port: `9000` (`main.cpp`)
- Game loop target: ~60 FPS / 16ms sleep (`main.cpp`)

## Character Roles
Three role types used throughout `GameLogic` and `Packet.h`:
- `Striker` (0) — speed multiplier 1.2×
- `Guardian` (1) — speed multiplier 0.8×
- `Manipulator` (2) — speed multiplier 1.0×
