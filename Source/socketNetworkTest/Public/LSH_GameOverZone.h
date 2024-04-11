// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSH_GameOverZone.generated.h"

UCLASS()
class SOCKETNETWORKTEST_API ALSH_GameOverZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSH_GameOverZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* boxcomponent;

};
