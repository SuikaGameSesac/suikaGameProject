// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerQuitWidget.h"

#include "LSH_FruitManager.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UServerQuitWidget::NativeConstruct()
{
	Super::NativeConstruct();

    // ��ư ������ C++ �ڵ带 ���ε��մϴ�.
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
        // MySocketActor���� ���� ���� ���� �Լ� ȣ��
        MySocketActor->CloseSocket();
    }
}
