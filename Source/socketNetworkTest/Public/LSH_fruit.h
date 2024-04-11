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

	UPROPERTY()
	bool inHand;

	UFUNCTION()
	void setFruitLocation(bool isGrab, float yPosition);

	UFUNCTION()
	void setCurrentPhysics(double yPosition, bool isGrab, bool state);

	UFUNCTION()
	void setPhysics(bool state);

	UFUNCTION()
	void GameOverEvent();

	bool IsOverlapOnce = false; //게임오버존 오버랩이 두번째인지

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundCue* popCue; // 사운드 큐 변수

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundWave* popSound; // 사운드 웨이브 변수

	bool playSoundOnce=false;
};
