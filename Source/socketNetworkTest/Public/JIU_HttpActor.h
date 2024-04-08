// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "JIU_HttpActor.generated.h"

UCLASS()
class SOCKETNETWORKTEST_API AJIU_HttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJIU_HttpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString ServerUrl = TEXT("http://127.0.0.1:8000/video/");

	class AJIU_HttpGameModeBase* gm;

	void ReqWebImage();

	void ResWebImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
