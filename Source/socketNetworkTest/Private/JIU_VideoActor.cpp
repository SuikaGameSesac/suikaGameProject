// Fill out your copyright notice in the Description page of Project Settings.


#include "JIU_VideoActor.h"

#include "JIU_VideoWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
AJIU_VideoActor::AJIU_VideoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트로 사용할 컴포넌트 생성
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);

	WidgetComponent->SetWidgetClass(VideoWidgetFactory);
	WidgetComponent->SetDrawSize(FVector2D(640, 320));

	WidgetComponent->SetRelativeRotation(FRotator(0, 90.0f, 0));
	WidgetComponent->SetRelativeScale3D(FVector(0.25f));

	if (WidgetComponent->GetWidget())
	{
		if (Cast<UJIU_VideoWidget>(WidgetComponent->GetWidget()))
		{

			VideoWidget = Cast<UJIU_VideoWidget>(WidgetComponent->GetWidget());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cast Fail"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Get Widget Fail"));
	}
}

// Called when the game starts or when spawned
void AJIU_VideoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJIU_VideoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

