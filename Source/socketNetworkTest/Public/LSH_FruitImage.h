// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "LSH_FruitImage.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETNETWORKTEST_API ULSH_FruitImage : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
    ULSH_FruitImage(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UImage* img_fruit;

    UPROPERTY(EditAnywhere)
    TArray<UTexture2D*> ImageTextures;

    UFUNCTION(BlueprintCallable)
    void ChangeImage(int i=0);

    int32 CurrentImageIndex = 0;
    FTimerHandle TimerHandle;


};
