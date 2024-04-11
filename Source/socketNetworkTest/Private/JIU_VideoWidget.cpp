// Fill out your copyright notice in the Description page of Project Settings.


#include "JIU_VideoWidget.h"

#include "JIU_HttpGameModeBase.h"
#include "Components/Image.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"

void UJIU_VideoWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UJIU_VideoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UJIU_VideoWidget::SetImage(UTexture2D* texture)
{
    UE_LOG(LogTemp, Warning, TEXT("UJIU_VideoWidget::SetWebImage"));

    Image_video->SetBrushFromTexture(texture);
}
