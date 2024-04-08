// Fill out your copyright notice in the Description page of Project Settings.


#include "JIU_HttpGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "JIU_VideoWidget.h"
#include "JIU_HttpActor.h"

void AJIU_HttpGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (httpUIFactory)
	{
		// 비디오를 보여줄 위젯을 만들고 싶다
		httpUI = CreateWidget<UJIU_VideoWidget>(GetWorld(), httpUIFactory);
		if (httpUI)
		{
			httpUI->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("Success - Creat JIU_VideoWidget"));
		}

	}
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	// 통신을 주고받을 액터를 만들고 싶다
	httpActor = GetWorld()->SpawnActor<AJIU_HttpActor>(AJIU_HttpActor::StaticClass(), FVector(0), FRotator(0));

	UE_LOG(LogTemp, Warning, TEXT("Success - Creat JIU_HttpActor"));
}
