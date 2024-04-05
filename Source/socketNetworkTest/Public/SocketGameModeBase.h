// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SocketGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETNETWORKTEST_API ASocketGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	void ConnectToServer(const FString& IPAddress, int32 Port);
	
};
