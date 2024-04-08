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

    gm = Cast<AJIU_HttpGameModeBase>(GetWorld()->GetAuthGameMode());

}

void UJIU_VideoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UJIU_VideoWidget::SendHttpRequest()
{
    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UJIU_VideoWidget::OnHttpRequestComplete);
    HttpRequest->SetURL(ServerUrl);
    HttpRequest->SetVerb("GET");
    HttpRequest->ProcessRequest();
}

void UJIU_VideoWidget::OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
    if (bSuccess && Response.IsValid())
    {
        ImageData = Response->GetContent();
        bImageDataAvailable = true;

        UE_LOG(LogTemp, Warning, TEXT("HTTP Request Success"));


        if (bImageDataAvailable)
        {
            // 이미지 데이터 출력
            for (int32 i = 0; i < 10 && i < ImageData.Num(); ++i)
            {
                UE_LOG(LogTemp, Warning, TEXT("%02X"), ImageData[i]);
            }

            bImageDataAvailable = false;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("HTTP Request failed!"));
    }
}

void UJIU_VideoWidget::SetWebImage(UTexture2D* texture)
{
    UE_LOG(LogTemp, Warning, TEXT("UJIU_VideoWidget::SetWebImage"));

    Image_video->SetBrushFromTexture(texture);
}
