// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DodgeballPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL_API ADodgeballPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UReStartWidget> BP_ReStartWidget;/*绑定蓝图类，且限定其只能是UReStartWidget的子类；
	                                                                               这里只是提供一个条目以供绑定蓝图类，实际创建的对象是UReStartWidget的实例，下面同理*/

	void ShowReStartWidget();
	void HideReStartWidget();

	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UHUDWidget> BP_HUDWidget;

	void UpdateHealthPercent(float HealthPercent);

private:
	UPROPERTY() class UReStartWidget* ReStartWidget;//添加UPROPERTY()宏，确保垃圾回收器不会回收该指针，下面同理
	UPROPERTY() class UHUDWidget* HUDWidget;

protected:
	virtual void BeginPlay() override;
};

