// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JIU_VideoWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETNETWORKTEST_API UJIU_VideoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_video;

	void SetImage(UTexture2D* texture);
};
