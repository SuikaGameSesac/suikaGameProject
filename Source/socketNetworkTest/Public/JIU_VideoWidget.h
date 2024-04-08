// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
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

	class AJIU_HttpGameModeBase* gm;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_video;

	void SendHttpRequest();

	void OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

	FString ServerUrl = TEXT("http://127.0.0.1:8000/video/");

	TArray<uint8> ImageData;

	bool bImageDataAvailable = false;

	void SetWebImage(UTexture2D* texture);
};
