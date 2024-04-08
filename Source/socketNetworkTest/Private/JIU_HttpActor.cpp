// Fill out your copyright notice in the Description page of Project Settings.


#include "JIU_HttpActor.h"
#include "JIU_HttpLibrary.h"
#include "HttpModule.h"
#include "ImageUtils.h"
#include "JIU_HttpGameModeBase.h"
#include "JIU_VideoWidget.h"
#include "Interfaces/IHttpResponse.h"

// Sets default values
AJIU_HttpActor::AJIU_HttpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJIU_HttpActor::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<AJIU_HttpGameModeBase>(GetWorld()->GetAuthGameMode());

	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &AJIU_HttpActor::ReqWebImage, 0.1f, true);
}

// Called every frame
void AJIU_HttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJIU_HttpActor::ReqWebImage()
{
	TSharedPtr<IHttpRequest> req = FHttpModule::Get().CreateRequest();
	req->SetURL(ServerUrl);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("image/jpeg"));
	req->OnProcessRequestComplete().BindUObject(this, &AJIU_HttpActor::ResWebImage);
	req->ProcessRequest();
}

void AJIU_HttpActor::ResWebImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 바이트배열에 응답받은 콘텐츠를 가져오고싶다.
		TArray<uint8> buf = Response->GetContent();
		// 저장할 이미지의 경로를 정하고싶다.
		FString imgPath = FPaths::ProjectPersistentDownloadDir() + "/DownloadWebImage.jpeg";
		// FFileHelper의 Save함수를 통해 파일로 저장한다.
		FFileHelper::SaveArrayToFile(buf, *imgPath);
		// 바이트배열을 이미지로 변환한다.
		UTexture2D* texture = FImageUtils::ImportBufferAsTexture2D(buf);
		// 그 이미지를 UI에 적용한다.
		gm->httpUI->SetWebImage(texture);
	}
}
