// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "UObject/Interface.h"
#include "I_HealthBar.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_HealthBar : public UInterface
{
	GENERATED_BODY()
};

class INCURSION_CPP_API II_HealthBar
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InitialiseWidget();
	virtual void SetHealth(float CurrentHealth, float MaxHealth);
};
