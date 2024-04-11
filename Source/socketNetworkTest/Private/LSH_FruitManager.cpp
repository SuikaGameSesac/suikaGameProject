// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_FruitManager.h"
#include "LSH_fruit.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "ServerQuitWidget.h"
#include "Net/Core/Trace/NetTrace.h"
#include "Math/UnrealMathUtility.h"
#include "ImageUtils.h"
#include "JIU_VideoActor.h"
#include "JIU_VideoWidget.h"
#include "TextureResource.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALSH_FruitManager::ALSH_FruitManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Texture = UTexture2D::CreateTransient(640, 320, EPixelFormat::PF_R8G8B8A8);
}

// Called when the game starts or when spawned
void ALSH_FruitManager::BeginPlay()
{
	Super::BeginPlay();

	QuitUI = CreateWidget<UServerQuitWidget>(GetWorld(), QuitUIFactory);
	if (QuitUI)
	{
		// ����Ʈ�� ���� �߰�
		QuitUI->AddToViewport();
	}

    VideoActor = GetWorld()->SpawnActor<AJIU_VideoActor>(VideoActorFactory, FVector(0.f, 0.f, 220.f), FRotator(90.f, -90.f, 0.f));

    if (VideoActor)
    {
        VideoWidget = VideoActor->VideoWidget;
        UE_LOG(LogTemp, Warning, TEXT("Find Video Actor!!!"));
    }

    if (VideoWidget)
    {
        // VideoWidget->SetImage(Texture);
        UE_LOG(LogTemp, Warning, TEXT("Find Widget Video!!!"));
    }

    FTimerHandle myTimerHandle;
    //�̰� ����
    //GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
        //{
         //   CreateFruit(GetActorLocation() + FMath::VRand() * 100, 0);
          //  GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
        //}), 0.5f, true);

	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, this, &ALSH_FruitManager::DataReceive, 0.1f, true);

	ChangeGameState(ESuikaGameState::GameReady);
}

// Called every frame
void ALSH_FruitManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //UE_LOG(LogTemp, Log, TEXT("Received Number: %d, Received Bool: %s"), currentYPosition, currentIsGrab ? TEXT("True") : TEXT("False"));
    // ���⼭ �ٸ� �۾� ���� ����

    if (bCreate && !inHand && -10.0f <= yPosition && yPosition <= 10.0f && isGrab) {
        inHand = true;
        if (currentFruit)
        {
            currentFruit->setFruitLocation(isGrab, yPosition);
            UE_LOG(LogTemp, Warning, TEXT("Hand?"))
        }
    }

    if(bCreate && isGrab  && inHand)
    {
        if(currentFruit)
			currentFruit->setFruitLocation(isGrab, yPosition);
    }

    if (!isGrab && inHand)
    {
        
        bCreate = false;
	    inHand = false;
	    auto finalYPosition = yPosition;
	    currentFruit->setCurrentPhysics(finalYPosition, isGrab, true);
    }
}

void ALSH_FruitManager::CreateFruit(FVector createLocation, int level)
{
    currentFruit = nullptr;
    bCreate = true;
    ALSH_fruit* fruit = GetWorld()->SpawnActor<ALSH_fruit>(fruitFactory);
    fruit->setPhysics(false);
    currentFruit = fruit;

	if(fruit != nullptr)
	{
		fruit->SetActorLocation(createLocation);
		fruit->manager = this;
		fruit->level = level;
	}
}

void ALSH_FruitManager::CombineFruit(FVector createLocation, int level)
{
    ALSH_fruit* fruit = GetWorld()->SpawnActor<ALSH_fruit>(fruitFactory);
    fruit->setPhysics(true);
    if (fruit != nullptr)
    {
        fruit->SetActorLocation(createLocation);
        fruit->manager = this;
        fruit->level = level;
    }
}

void ALSH_FruitManager::AfterHitEvent(FVector hitLoc, int fruitLevel)
{
	if (hitLoc == pastCreateLocation)return;
	
	UE_LOG(LogTemp, Warning, TEXT("%d %d %d"), hitLoc.X, hitLoc.Y, hitLoc.Z);
	pastCreateLocation = hitLoc;

	++fruitLevel;

	CombineFruit(hitLoc, fruitLevel);
}

void ALSH_FruitManager::ChangeGameState(ESuikaGameState NewState)
{
	CurrentGameState = NewState;

	switch (NewState)
	{
	case ESuikaGameState::GameReady:
		ConnectToServer(ServerIP, ServerPort);
		break;
	case ESuikaGameState::GamePlaying:
        if(!bCreate)
			CreateFruit(FVector3d(0,0,270), FMath::RandRange(0, 2));
		break;
    case ESuikaGameState::GameFinish:
        ChangeGameState(ESuikaGameState::GamePlaying);
        break;
	case ESuikaGameState::GameExit:
		CloseSocket();
		break;
	}
}

void ALSH_FruitManager::ConnectToServer(const FString& IPAddress, int32 Port)
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

        // ������ ����
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

        // ������ ����
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
    ChangeGameState(ESuikaGameState::GamePlaying);
}

void ALSH_FruitManager::CloseSocket()
{
    // Close the socket
    socket->Close();
    UE_LOG(LogTemp, Error, TEXT("Server Close"));
    // Set socket to nullptr to indicate it is closed
}

bool bExpectingNumber = true; // ������ ����ϴ� ���� �������� ���θ� ��Ÿ���� �÷���
int32 LastNumberValue = 0; // ������ ���ŵ� ���� ��

void ALSH_FruitManager::DataReceive()
{
    uint8 Buffer[65432]; // �����͸� ������ ����
    int32 BytesRead = 0; // ������ ����Ʈ ��
    if (socket->Recv(Buffer, sizeof(Buffer), BytesRead))
    {
        FString ReceivedMessage = FString(UTF8_TO_TCHAR(Buffer)); // ������ �����͸� FString���� ��ȯ

        // ������ �����͸� ������ �������� �����Ͽ� �迭�� ����
        TArray<FString> Values;
        ReceivedMessage.ParseIntoArray(Values, TEXT(" "), true);

        // �迭�� ��ȸ�ϸ鼭 ���� ó��
        for (const FString& Value : Values)
        {
            if (bExpectingNumber) // ���� ���� ���̶�� ����ϴ� ���
            {
                if (Value.IsNumeric()) // ���� ���� ������ ���
                {
                    // ���ڷ� ��ȯ�Ͽ� ���� -> ��ǥ ��
                    LastNumberValue = FCString::Atoi(*Value);
                    bExpectingNumber = false; // ���� ���� �ο� ���̶�� ���
                }
            }
            else if (Value.StartsWith(TEXT("/")))
            {
                uint32 size = Value.Len();
                TArray<uint8> BinaryData;
                BinaryData.AddUninitialized(size);
            	StringToBytes(Value, BinaryData.GetData(), size);


                // �ؽ��� �����ͷ� ä��ϴ�.
                FTexture2DMipMap& Mip = Texture->PlatformData->Mips[0];
                void* DataPtr = Mip.BulkData.Lock(LOCK_READ_WRITE);
                FMemory::Memcpy(DataPtr, BinaryData.GetData(), BinaryData.Num());
                Mip.BulkData.Unlock();

                // �ؽ��� ������ ������Ʈ�մϴ�.
                // Texture->PlatformData->NumSlices = 1;
                Texture->PlatformData->PixelFormat = PF_R8G8B8A8;

                // UpdateResource�� ȣ���Ͽ� �ؽ�ó ������Ʈ
                Texture->UpdateResource();
            }
            else // ���� �ο� ���̶�� ����ϴ� ���
            {
                bool BoolValue = false; // �ο� �� ������ ���� ���� 

                // ���� ���� "True"���� "False"���� ��ҹ��� ���� ���� Ȯ���Ͽ� �ο� �� ����
                if (Value.Equals(TEXT("True"), ESearchCase::IgnoreCase))
                {
                    BoolValue = true;
                }
                else if (Value.Equals(TEXT("False"), ESearchCase::IgnoreCase))
                {
                    BoolValue = false;
                }
                
                yPosition = MapIntValue(LastNumberValue, 0, 640, -85.0f, 85.0f);
                isGrab = BoolValue;
                setServerQeust(yPosition, isGrab);

                // ���� ���� �ο� �� ���
                //UE_LOG(LogTemp, Error, TEXT("Received Number: %d, Received Bool: %s"), yPosition, BoolValue ? TEXT("True") : TEXT("False"));

                bExpectingNumber = true; // ���� ���� ���� ���̶�� ���
            }
        }
    }
}

float ALSH_FruitManager::MapIntValue(int32 value, int32 inMin, int32 inMax, float outMin, float outMax)
{
	float floatValue = static_cast<float>(value);
    return FMath::GetMappedRangeValueClamped(FVector2D(inMin, inMax), FVector2D(outMin, outMax), floatValue);
}

void ALSH_FruitManager::setServerQeust(float syPosition, bool sisGrab)
{
    currentYPosition = syPosition;
    currentIsGrab = sisGrab;
    //UE_LOG(LogTemp, Warning, TEXT("Received Number: %d, Received Bool: %s"), currentYPosition, currentIsGrab ? TEXT("True") : TEXT("False"));
}
