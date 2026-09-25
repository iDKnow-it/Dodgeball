// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DODGEBALL_API IHealthInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = Health) 
	void OnDeath();
	virtual void OnDeath_Implementation() = 0;//接口的纯虚函数告诉调用者这里应该有一个实现，调用者必须在继承类中实现这个函数，否则编译器会报错。类似于一个强制的提醒,下面同理

	UFUNCTION(BlueprintNativeEvent, Category = Health)
	void OnTakeDamage();
	virtual void OnTakeDamage_Implementation() = 0;

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
