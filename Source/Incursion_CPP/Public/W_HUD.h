// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "W_HUD_Ammo.h"
#include "W_HUD_HealthBar.h"
#include "W_HUD_Lives.h"
#include "W_HUD_SkipCountdown.h"
#include "W_HUD_Timer.h"

#include "W_HUD.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

	// Lives Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_Lives> WidgetLivesClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_Lives* WidgetLives;

	// Health Bar
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_HealthBar> WidgetClassHealthBar;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_HealthBar* WidgetHealthBar;

	// Ammo Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_Ammo> WidgetAmmoClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_Ammo* WidgetAmmo;

	// Wave Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_Timer> WidgetTimerClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_Timer* WidgetTimer;

	// Ammo Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_SkipCountdown> WidgetSkipCountdownClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_SkipCountdown* WidgetSkipCountdown;
};
