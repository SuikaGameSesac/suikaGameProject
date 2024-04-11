// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_FruitImage.h"

ULSH_FruitImage::ULSH_FruitImage(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    if (ImageTextures.IsEmpty())
    {
        ImageTextures.Add(LoadObject<UTexture2D>(this, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/furit_mark17_cherry.furit_mark17_cherry'")));
        //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_strawberry.fruit_strawberry'")));
        //ImageTextures.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_dekopon.fruit_dekopon'")));
        ImageTextures.Add(LoadObject<UTexture2D>(this, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_kaki.fruit_kaki'")));
        ImageTextures.Add(LoadObject<UTexture2D>(this, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_apple.fruit_apple'")));
        ImageTextures.Add(LoadObject<UTexture2D>(this, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_nashi.fruit_nashi'")));
        ImageTextures.Add(LoadObject<UTexture2D>(this, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/color08_pink_peach.color08_pink_peach'")));
        ImageTextures.Add(LoadObject<UTexture2D>(this, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_melon.fruit_melon'")));
        ImageTextures.Add(LoadObject<UTexture2D>(this, TEXT("/Script/Engine.Texture2D'/Game/LSH/img/fruit_suika_kodama.fruit_suika_kodama'")));
    }
}

void ULSH_FruitImage::NativeConstruct()
{
	Super::NativeConstruct();

}


void ULSH_FruitImage::ChangeImage(int i)
{
    //UE_LOG(LogTemp, Warning, TEXT("%d"), i);
    img_fruit->SetBrushFromTexture(ImageTextures[i]);
    //img_fruit->setsize
}

