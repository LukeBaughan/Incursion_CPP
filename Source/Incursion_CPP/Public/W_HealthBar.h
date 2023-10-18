// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BFL_Incursion.h"
#include "Blueprint/UserWidget.h"
#include "I_HealthBar.h"

#include "W_HealthBar.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HealthBar : public UUserWidget, public II_HealthBar
{
	GENERATED_BODY()
		
public:
	UFUNCTION(BlueprintNativeEvent)
		void InitialiseWidget() override;

	void SetHealth(float CurrentHealth, float MaxHealth) override;

	// Set in blueprint
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UProgressBar* ProgressBarHealth;

private:
	UBFL_Incursion* BFL_Incursion;
};
