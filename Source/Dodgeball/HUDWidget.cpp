// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "DodgeballPlayerController.h"

void UHUDWidget::UpdateHealthBar(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}

