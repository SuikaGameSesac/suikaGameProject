// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_GameOverZone.h"
#include "Components/BoxComponent.h"
#include "LSH_fruit.h"

// Sets default values
ALSH_GameOverZone::ALSH_GameOverZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxcomponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	this->SetRootComponent(boxcomponent);
}

// Called when the game starts or when spawned
void ALSH_GameOverZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALSH_GameOverZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALSH_GameOverZone::NotifyActorEndOverlap(AActor* OtherActor)
{
	ALSH_fruit* fruit = Cast<ALSH_fruit>(OtherActor);
	if (fruit)
	{
		fruit->GameOverEvent();
	}
}