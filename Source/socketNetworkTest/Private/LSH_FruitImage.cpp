// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_FruitImage.h"

ULSH_FruitImage::ULSH_FruitImage(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ImageTextures.Reset();
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/furit_mark17_cherry.furit_mark17_cherry'")));
    ////ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_strawberry.fruit_strawberry'")));
    ////ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_dekopon.fruit_dekopon'")));
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_kaki.fruit_kaki'")));
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_apple.fruit_apple'")));
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_nashi.fruit_nashi'")));
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/color08_pink_peach.color08_pink_peach'")));
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_melon.fruit_melon'")));
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_suika_kodama.fruit_suika_kodama'")));
}

void ULSH_FruitImage::NativeConstruct()
{
	Super::NativeConstruct();



    // 이미지 텍스처 배열 초기화
    //static ConstructorHelpers::FObjectFinder<UTexture2D> Texture1(TEXT("/Script/Engine.Texture2D'/Game/LSH/img/furit_mark17_cherry.furit_mark17_cherry'"));
    //static ConstructorHelpers::FObjectFinder<UTexture2D> Texture2(TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_strawberry.fruit_strawberry'"));
    //static ConstructorHelpers::FObjectFinder<UTexture2D> Texture3(TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_budou_kyohou.fruit_budou_kyohou'"));
    
    ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/furit_mark17_cherry.furit_mark17_cherry'")));
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_strawberry.fruit_strawberry'")));
    //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_dekopon.fruit_dekopon'")));
    ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_kaki.fruit_kaki'")));
    ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_apple.fruit_apple'")));
    ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_nashi.fruit_nashi'")));
    ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/color08_pink_peach.color08_pink_peach'")));
    ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_melon.fruit_melon'")));
    ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_suika_kodama.fruit_suika_kodama'")));

    //ChangeImage(0);

    //GetWorldTimerManager().SetTimerForNextTick(this, &ULSH_FruitImage::ChangeImage);
}

void ULSH_FruitImage::ChangeImage(int i)
{
    ImageTextures;
    //img_fruit->SetBrushFromTexture(ImageTextures[i]);
}