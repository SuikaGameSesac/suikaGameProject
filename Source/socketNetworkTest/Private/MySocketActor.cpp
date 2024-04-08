// Fill out your copyright notice in the Description page of Project Settings.


#include "MySocketActor.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "ServerQuitWidget.h"


// Called when the game starts or when spawned
void AMySocketActor::BeginPlay()
{
	Super::BeginPlay();

    QuitUI = CreateWidget<UServerQuitWidget>(GetWorld(), QuitUIFactory);
    if (QuitUI)
    {
        // 뷰포트에 위젯 추가
        QuitUI->AddToViewport();
    }

	FTimerHandle TimerHandle;

    // 0.1초마다 DataReceive 함수 호출 데이터 수신!!
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMySocketActor::DataReceive, 0.1f, true);

    //TArray<uint8> ReceivedData;

    // 0.1초마다 DataReceive 함수 호출 데이터 수신!!
    //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMySocketActor::DataReceive, 1.0f, true);


    ChangeGameState(ESuikaGameState::GameReady);
}

// Called every frame
void AMySocketActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySocketActor::ChangeGameState(ESuikaGameState NewState)
{
    CurrentGameState = NewState;

    switch (NewState)
    {
    case ESuikaGameState::GameReady:
        ConnectToServer(ServerIP, ServerPort);
        break;
    case ESuikaGameState::GamePlaying:
        // Do something when game starts playing
        break;
    case ESuikaGameState::GameExit:
        CloseSocket();
        break;
    }
}

void AMySocketActor::ConnectToServer(const FString& IPAddress, int32 Port)
{
    FIPv4Address ip;
    FIPv4Address::Parse(IPAddress, ip);

    TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    addr->SetIp(ip.Value);
    addr->SetPort(Port);

    socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
    if (socket->Connect(addr.Get()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Server Success"))

        // 데이터 전송
        FString Message = TEXT("Message_Send buffer");
        int32 BytesSent = 0;
        TArray<uint8> SendBuffer;
        const TCHAR* MessagePtr = *Message;
        int32 MessageLength = FCString::Strlen(MessagePtr);
        SendBuffer.AddUninitialized(MessageLength);
        for (int32 i = 0; i < MessageLength; ++i)
        {
            SendBuffer[i] = static_cast<uint8>(MessagePtr[i]);
        }
        socket->Send(SendBuffer.GetData(), SendBuffer.Num(), BytesSent);

        // 데이터 수신
        uint8 Buffer[1024];
        int32 BytesRead = 0;
        if (socket->Recv(Buffer, sizeof(Buffer), BytesRead))
        {
            FString ReceivedMessage = FString(UTF8_TO_TCHAR(Buffer));
            UE_LOG(LogTemp, Warning, TEXT("Server Message: %s"), *ReceivedMessage);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Server Fail"));
    }
}

void AMySocketActor::CloseSocket()
{
    // Close the socket
    socket->Close();
    UE_LOG(LogTemp, Error, TEXT("Server Close"));
    // Set socket to nullptr to indicate it is closed
}

void AMySocketActor::DataReceive()
{
    uint8 Buffer[1024];
    int32 BytesRead = 0;
    if (socket->Recv(Buffer, sizeof(Buffer), BytesRead))
    {
        FString ReceivedMessage = FString(UTF8_TO_TCHAR(Buffer));
            UE_LOG(LogTemp, Warning, TEXT("Server Message: %s"), *ReceivedMessage);
    }
}

