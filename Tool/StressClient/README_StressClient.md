# StressClient

Temporary TCP stress client for the local game server.

Default target:

```powershell
.\StressClient.exe --host 127.0.0.1 --port 9000 --clients 16 --duration 60 --scenario room
```

Recommended test order:

```powershell
.\StressClient.exe --scenario connect --clients 30 --duration 60
.\StressClient.exe --scenario register --clients 30 --duration 60 --user-prefix load --password pass1234
.\StressClient.exe --scenario login --clients 30 --duration 300 --user-prefix load --password pass1234
.\StressClient.exe --scenario room --clients 30 --duration 300 --user-prefix load --password pass1234
```

`move` sends `PKT_C2S_MOVE_KEYINPUT` after room creation, ready, and game start. Use it only after the server moves sessions to `INGAME` state after game start; otherwise the server is expected to reject/disconnect move packets while the session remains in `ROOM`.

Useful options:

```text
--host 127.0.0.1
--port 9000
--clients 16
--duration 60
--scenario connect|register|login|room|move
--user-prefix load
--user-start 1
--password pass1234
--hold-ms 1000
--move-hz 10
--recv-timeout-ms 3000
--start-delay-ms 10
```

The test expects database accounts such as `load0001`, `load0002`, ... for login/room scenarios. Run `register` first if the accounts do not exist.
