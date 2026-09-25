// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API UReStartWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget)) class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget)) class UButton* QuitButton;

	virtual void NativeOnInitialized() override;	

protected:
	UFUNCTION()
	void OnRestartButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();
};
