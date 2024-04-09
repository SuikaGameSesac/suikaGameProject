// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_FruitManager.h"
#include "LSH_fruit.h"
#include "gameWidget.h"

// Sets default values
ALSH_FruitManager::ALSH_FruitManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALSH_FruitManager::BeginPlay()
{
	Super::BeginPlay();

	widget = CreateWidget<UgameWidget>(GetWorld(), gameUIFactory);
	widget->AddToViewport();

    FTimerHandle myTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
        {
            CreateFruit(GetActorLocation() + FMath::VRand() * 100, 0);
            GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
        }), 0.5f, true);
}

// Called every frame
void ALSH_FruitManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALSH_FruitManager::CreateFruit(FVector createLocation, int level)
{
    ALSH_fruit* fruit = GetWorld()->SpawnActor<ALSH_fruit>(fruitFactory);

	if(fruit != nullptr)
	{
		fruit->SetActorLocation(createLocation);
		fruit->manager = this;
		fruit->level = level;
	}

	

}

void ALSH_FruitManager::AfterHitEvent(FVector hitLoc, int fruitLevel)
{
	if (fruitLevel == 6 || hitLoc == pastCreateLocation)return;
	
	//UE_LOG(LogTemp, Warning, TEXT("%d %d %d"), hitLoc.X, hitLoc.Y, hitLoc.Z);
	pastCreateLocation = hitLoc;

	++fruitLevel;

	CreateFruit(hitLoc, fruitLevel);

	//score
	switch (fruitLevel)
	{
	case 1:
		score += 1;
		break;
	case 2:
		score += 6;
		break;
	case 3:
		score += 15;
		break;
	case 4:
		score += 28;
		break;
	case 5:
		score += 45;
		break;
	case 6:
		score += 66;
		break;
	default:
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("now score : %d"), score);
	widget->SetScoreText(score);
}