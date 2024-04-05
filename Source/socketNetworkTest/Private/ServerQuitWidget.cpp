// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerQuitWidget.h"

#include "MySocketActor.h"
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
    AMySocketActor* MySocketActor = Cast<AMySocketActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMySocketActor::StaticClass()));

    if (MySocketActor)
    {
        // MySocketActor���� ���� ���� ���� �Լ� ȣ��
        MySocketActor->CloseSocket();
    }
}
