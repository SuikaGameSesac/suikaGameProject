// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "gameWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETNETWORKTEST_API UgameWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_0;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_start;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* txt_score;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* cna_gameover;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_rerty;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_quit;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class ULSH_FruitImage* nextFruitImage;

	UFUNCTION()
	void GameStart();

	UFUNCTION()
	void ReGame();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void OpenLevel();

	UFUNCTION()
	void SetScoreText(int i);

	UFUNCTION()
	void SetNextFruitIMG(int i);

};
