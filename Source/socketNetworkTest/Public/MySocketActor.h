// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LSH_FruitManager.h"
#include "GameFramework/Actor.h"
#include "MySocketActor.generated.h"

UENUM(BlueprintType)
enum class ESuikaGameState : uint8
{
	GameReady,
	GamePlaying,
	GameExit,
};

DECLARE_EVENT_TwoParams(AMySocketActor, FSocketDataUpdateEvent, int32, bool);

UCLASS()
class SOCKETNETWORKTEST_API AMySocketActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSH_FruitManager* fruitManagerRef = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FSocket* socket;
	ESuikaGameState CurrentGameState;
	FString ServerIP = TEXT("127.0.0.1");
	int32 ServerPort = 65432;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeGameState(ESuikaGameState NewState); // Change access modifier to public

	void ConnectToServer(const FString& IPAddress, int32 Port);

	UFUNCTION(BlueprintCallable)
	void CloseSocket();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UServerQuitWidget> QuitUIFactory;

	UPROPERTY()
	class UServerQuitWidget* QuitUI;

	UFUNCTION()
	void DataReceive();

public:
	FSocketDataUpdateEvent& OnSocketDataUpdate() { return SocketDataUpdateEvent; }

private:
	FSocketDataUpdateEvent SocketDataUpdateEvent;

};
