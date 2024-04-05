// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_fruit.h"
#include "Components/SphereComponent.h"


// Sets default values
ALSH_fruit::ALSH_fruit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spherecomponent = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComponent"));
	this->SetRootComponent(spherecomponent);
	spherecomponent->SetSphereRadius(5.0f);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(0.1f));
}

// Called when the game starts or when spawned
void ALSH_fruit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALSH_fruit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//액터의 y축 고정
	auto loc = GetActorLocation();
	SetActorLocation(FVector(loc.X, 0, loc.Z));
}

