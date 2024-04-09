// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSH_FruitManager.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	FVector pastCreateLocation;//To prevent fruit crash events from happening twice

	UFUNCTION()
	void CreateFruit(FVector createLocation, int level);

	UPROPERTY()
	FVector fruitDropLocation;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALSH_fruit> fruitFactory;

	UFUNCTION()
	void AfterHitEvent(FVector hitLoc, int fruitLevel);

	UPROPERTY(BlueprintReadOnly)
	int32 score = 0;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UgameWidget> gameUIFactory;

	UPROPERTY()
	class UgameWidget* widget;

};
