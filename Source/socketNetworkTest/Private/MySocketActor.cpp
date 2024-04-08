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

bool bExpectingNumber = true; // 다음에 기대하는 값이 숫자인지 여부를 나타내는 플래그
int32 LastNumberValue = 0; // 이전에 수신된 숫자 값

void AMySocketActor::DataReceive()
{
    uint8 Buffer[1024]; // 데이터를 수신할 버퍼
    int32 BytesRead = 0; // 수신한 바이트 수
    if (socket->Recv(Buffer, sizeof(Buffer), BytesRead))
    {
        FString ReceivedMessage = FString(UTF8_TO_TCHAR(Buffer)); // 수신한 데이터를 FString으로 변환

        // 수신한 데이터를 공백을 기준으로 분할하여 배열에 저장
        TArray<FString> Values;
        ReceivedMessage.ParseIntoArray(Values, TEXT(" "), true);

        // 배열을 순회하면서 값을 처리
        for (const FString& Value : Values)
        {
            if (bExpectingNumber) // 현재 숫자 값이라고 기대하는 경우
            {
                if (Value.IsNumeric()) // 현재 값이 숫자인 경우
                {
                    // 숫자로 변환하여 저장 -> 좌표 값
                    LastNumberValue = FCString::Atoi(*Value);
                    bExpectingNumber = false; // 다음 값은 부울 값이라고 기대
                }
            }
            else // 현재 부울 값이라고 기대하는 경우
            {
                bool BoolValue = false; // 부울 값 저장을 위한 변수 

                // 현재 값이 "True"인지 "False"인지 대소문자 구분 없이 확인하여 부울 값 설정
                if (Value.Equals(TEXT("True"), ESearchCase::IgnoreCase))
                {
                    BoolValue = true;
                }
                else if (Value.Equals(TEXT("False"), ESearchCase::IgnoreCase))
                {
                    BoolValue = false;
                }

                OnSocketDataUpdate().Broadcast(LastNumberValue, BoolValue);
                                
                // 숫자 값과 부울 값 출력
                UE_LOG(LogTemp, Warning, TEXT("Received Number: %d, Received Bool: %s"), LastNumberValue, BoolValue ? TEXT("True") : TEXT("False"));

                bExpectingNumber = true; // 다음 값은 숫자 값이라고 기대
            }
        }
    }
}
