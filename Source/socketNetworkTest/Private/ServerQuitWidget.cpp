// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerQuitWidget.h"

#include "LSH_FruitManager.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UServerQuitWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 버튼 위젯과 C++ 코드를 바인딩합니다.
    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UServerQuitWidget::OnButtonClicked);
    }
}

void UServerQuitWidget::OnButtonClicked()
{
    ALSH_FruitManager* MySocketActor = Cast<ALSH_FruitManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ALSH_FruitManager::StaticClass()));

    if (MySocketActor)
    {
        // MySocketActor에서 게임 상태 변경 함수 호출
        MySocketActor->CloseSocket();
    }
}