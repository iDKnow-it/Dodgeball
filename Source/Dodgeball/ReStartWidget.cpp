// Fill out your copyright notice in the Description page of Project Settings.


#include "ReStartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "DodgeballPlayerController.h"

void UReStartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
		RestartButton->OnClicked.AddDynamic(this, &UReStartWidget::OnRestartButtonClicked);

		QuitButton->OnClicked.AddDynamic(this, &UReStartWidget::OnQuitButtonClicked);
}

void UReStartWidget::OnRestartButtonClicked()
{
	if (RestartButton != nullptr)
	{
		ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
		if (PlayerController)
		{
			PlayerController->HideReStartWidget();
		}
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void UReStartWidget::OnQuitButtonClicked()
{
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
