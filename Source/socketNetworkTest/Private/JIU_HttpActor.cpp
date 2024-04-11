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
}

// Called every frame
void AJIU_HttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
