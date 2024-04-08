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
		// ����Ʈ�迭�� ������� �������� ��������ʹ�.
		TArray<uint8> buf = Response->GetContent();
		// ������ �̹����� ��θ� ���ϰ�ʹ�.
		FString imgPath = FPaths::ProjectPersistentDownloadDir() + "/DownloadWebImage.jpeg";
		// FFileHelper�� Save�Լ��� ���� ���Ϸ� �����Ѵ�.
		FFileHelper::SaveArrayToFile(buf, *imgPath);
		// ����Ʈ�迭�� �̹����� ��ȯ�Ѵ�.
		UTexture2D* texture = FImageUtils::ImportBufferAsTexture2D(buf);
		// �� �̹����� UI�� �����Ѵ�.
		gm->httpUI->SetWebImage(texture);
	}
}
