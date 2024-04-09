// Fill out your copyright notice in the Description page of Project Settings.


#include "gameWidget.h"


#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "LSH_FruitImage.h"

void UgameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_start->OnClicked.AddDynamic(this, &UgameWidget::GameStart);
	btn_rerty->OnClicked.AddDynamic(this, &UgameWidget::ReGame);
	btn_quit->OnClicked.AddDynamic(this, &UgameWidget::QuitGame);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void UgameWidget::GameStart() 
{
	UE_LOG(LogTemp, Warning, TEXT("Game Start!!"));
	WidgetSwitcher_0->SetActiveWidgetIndex(1);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	//다음 과일 이미지 테스트용 후에 삭제 필요
	int RandomInt = FMath::RandRange(0, 3);
	SetNextFruitIMG(RandomInt);
}

void UgameWidget::ReGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Restart Game!!"));

}

void UgameWidget::QuitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Quit Game!!"));

}

// 레벨을 오픈하는 함수
void UgameWidget::OpenLevel()
{
	// 현재 플레이 중인 레벨의 이름을 얻습니다.
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);

	// 해당 레벨을 재시작합니다.
	UGameplayStatics::OpenLevel(GetWorld(), *CurrentLevelName);
}

void UgameWidget::SetNextFruitIMG(int i)
{
	if(nextFruitImage)nextFruitImage->ChangeImage(i);
}


void UgameWidget::SetScoreText(int i)
{
	if(txt_score)txt_score->SetText(FText::AsNumber(i));
}