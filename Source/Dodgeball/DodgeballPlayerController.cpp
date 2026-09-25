// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballPlayerController.h"
#include "ReStartWidget.h"
#include "HUDWidget.h"

void ADodgeballPlayerController::ShowReStartWidget()
{
	if (BP_ReStartWidget != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		ReStartWidget = CreateWidget<UReStartWidget>(this, BP_ReStartWidget);
		if (ReStartWidget != nullptr)
		{
			ReStartWidget->AddToViewport();
		}
	}
}

void ADodgeballPlayerController::HideReStartWidget()
{
	if (ReStartWidget)
	{ 
		ReStartWidget->RemoveFromParent();
		ReStartWidget->Destruct();
		ReStartWidget = nullptr;
	}
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}



void ADodgeballPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (BP_HUDWidget)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::UpdateHealthPercent(float HealthPercent)
{
	if (HUDWidget)
	{
		HUDWidget->UpdateHealthBar(HealthPercent);
	}
}