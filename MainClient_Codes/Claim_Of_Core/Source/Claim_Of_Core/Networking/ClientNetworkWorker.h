#pragma once

#include "CoreMinimal.h"

#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "HAL/Event.h"
#include "Containers/Queue.h"

#include "ClientNetworkTypes.h"

class FSocket;

class FClientNetworkWorker : public FRunnable
{
public:
    FClientNetworkWorker();
    virtual ~FClientNetworkWorker() override;

    // --- FRunnable interface ---
    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;
    virtual void Exit() override;

    // --- Queue access (thread-safe) ---
    TQueue<FNetCommand, EQueueMode::Mpsc>  InboundCommandQueue;   // Main → Worker
    TQueue<FNetEvent,   EQueueMode::Spsc>  OutboundEventQueue;    // Worker → Main

    void WakeUp();

private:
    // Socket operations (worker thread only)
    bool TryConnectBlocking(const FString& IP, int32 Port);
    void CloseSocket();

    // Command / packet processing
    void FlushInboundCommands();
    void RecvAndParsePackets();
    void HandlePacket(FPacketHeader* Header, uint8* PayloadData, uint16 PayloadSize);
    void SendRawPacket(uint16 PacketID, const TArray<uint8>& Payload);

    // Event helpers
    void PushEvent(FNetEvent&& Event);

    // Reconnection state machine
    void HandleReconnect();

    FSocket* Socket;
    TArray<uint8> RecvBuffer;

    FRunnableThread* Thread;
    FEvent* WakeEvent;
    TAtomic<bool> bStopRequested;

    // Reconnection state
    FString ReconnectIP;
    int32 ReconnectPort = 0;
    int32 ReconnectRetryCount = 0;
    static constexpr int32 MaxReconnectRetries = 10;
    static constexpr float ReconnectIntervalSec = 3.0f;
    bool bReconnecting = false;
};
