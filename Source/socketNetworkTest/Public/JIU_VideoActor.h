// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JIU_VideoActor.generated.h"

UCLASS()
class SOCKETNETWORKTEST_API AJIU_VideoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJIU_VideoActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<class UJIU_VideoWidget> VideoWidgetFactory;

	UPROPERTY()
	class UWidgetComponent* WidgetComponent;

	UPROPERTY()
	class UJIU_VideoWidget* VideoWidget;
};
