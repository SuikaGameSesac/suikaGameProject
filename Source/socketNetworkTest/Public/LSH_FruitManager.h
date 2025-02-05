// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSH_FruitManager.generated.h"

UENUM(BlueprintType)
enum class ESuikaGameState : uint8
{
	GameReady,
	GamePlaying,
	GameFinish,
	GameExit,
};

UCLASS()
class SOCKETNETWORKTEST_API ALSH_FruitManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSH_FruitManager();

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

	UPROPERTY()
	FVector pastCreateLocation;//To prevent fruit crash events from happening twice

	UFUNCTION()
	void CreateFruit(FVector createLocation, int level);

	UFUNCTION()
	void CombineFruit(FVector createLocation, int level);

	UPROPERTY()
	FVector fruitDropLocation;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALSH_fruit> fruitFactory;

	UFUNCTION()
	void AfterHitEvent(FVector hitLoc, int fruitLevel);

	UPROPERTY()
	class ALSH_fruit* currentFruit;

	UPROPERTY(EditAnywhere)
	int32 yPosition = 320;

	UPROPERTY(EditAnywhere)
	bool isGrab = true;

	// ���� ����

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

	UPROPERTY()
	bool bCreate = false;
	UPROPERTY()
	bool inHand = false;

	UFUNCTION()
	float MapIntValue(int32 value, int32 inMin, int32 inMax, float outMin, float outMax);

	UFUNCTION()
	void setServerQeust(float syPosition, bool sisGrab);

	UPROPERTY(EditAnywhere)
	int32 currentYPosition = 0;

	UPROPERTY(EditAnywhere)
	bool currentIsGrab = true;

	UPROPERTY(EditAnywhere)
	bool bCurrentFruit = true;


	UPROPERTY(BlueprintReadOnly)
	int32 score = 0;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UgameWidget> gameUIFactory;

	UPROPERTY()
	class UgameWidget* widget;

	UPROPERTY()
	int nextFruit = 0;
};
