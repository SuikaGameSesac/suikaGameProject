// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSH_fruit.generated.h"

UCLASS()
class SOCKETNETWORKTEST_API ALSH_fruit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSH_fruit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* spherecomponent;

	UFUNCTION()
	void HitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);//event when fruit hit

	UPROPERTY()
	class ALSH_FruitManager* manager;

	UPROPERTY(BlueprintReadOnly)
	int level;

	bool doOnce = false;

	UFUNCTION()
	void DestroyActorWithDelay();

	UFUNCTION()
	void SetShow();

	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* fruitImageComp;

	UPROPERTY()
	class ULSH_FruitImage* fruitImage;
};
