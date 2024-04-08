// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_fruit.h"
#include "Components/SphereComponent.h"
#include "LSH_FruitManager.h"
#include <cmath>
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "LSH_FruitImage.h"



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

	spherecomponent->OnComponentHit.AddDynamic(this, &ALSH_fruit::HitEvent);

	fruitImageComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("fruitComp"));//위젯
	fruitImageComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALSH_fruit::BeginPlay()
{
	Super::BeginPlay();
	
	fruitImage = Cast<ULSH_FruitImage>(fruitImageComp->GetWidget());//위젯 캐스팅
	
	//if (fruitImage != nullptr)fruitImage->ChangeImage(level);

	GetWorldTimerManager().SetTimerForNextTick(this, &ALSH_fruit::SetShow);
}

// Called every frame
void ALSH_fruit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//액터의 y축 고정
	auto loc = GetActorLocation();
	SetActorLocation(FVector(loc.X, 0, loc.Z));
	auto r = fruitImageComp->GetComponentRotation();
	fruitImageComp->SetWorldRotation(FRotator(r.Pitch,90,r.Roll));
}

void ALSH_fruit::HitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ALSH_fruit* otherFruit = Cast<ALSH_fruit>(OtherActor);

	if (!doOnce && otherFruit != nullptr && otherFruit->level == level)
	{
		if (manager != nullptr)
		{
			manager->AfterHitEvent(Hit.Location, level);
		}

		doOnce = true;

		GetWorldTimerManager().SetTimerForNextTick(this, &ALSH_fruit::DestroyActorWithDelay);
	}
	
}

void ALSH_fruit::DestroyActorWithDelay()
{
	Destroy();
}

void ALSH_fruit::SetShow()
{
	FVector scale = ((pow(2.1f, level) * 0.1) + 1.0f) * FVector(1, 1, 1);
	SetActorScale3D(scale);
	if (fruitImage != nullptr)fruitImage->ChangeImage(level);
	float ActorSize = ((pow(2.1f, level) * 0.1) + 1.0f) / 25;
	float aa = 34.71901f * ((pow(2.1f, level) * 0.1) + 1.0f);
	//UE_LOG(LogTemp, Log, TEXT("%f"), (ActorSize - 1) * 25);
	//if(fruitImageComp!=nullptr)fruitImageComp->SetDrawSize(FVector2D(aa,aa));
	UE_LOG(LogTemp, Log, TEXT("%f"), aa);

}