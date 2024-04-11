// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerQuitWidget.generated.h"

/**
 *
 */
UCLASS()
class SOCKETNETWORKTEST_API UServerQuitWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
};