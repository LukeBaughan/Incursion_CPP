// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "W_HUD_Ammo.h"
#include "W_HUD_CantBuild.h"
#include "W_HUD_Crosshair.h"
#include "W_HUD_HealthBar.h"
#include "W_HUD_Lives.h"
#include "W_HUD_Points.h"
#include "W_HUD_SkipCountdown.h"
#include "W_HUD_Timer.h"
#include "W_HUD_Wave.h"
#include "W_Widget.h"

#include "W_HUD.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UPROPERTY(BlueprintReadWrite)
		TArray<UW_Widget*> AllWidgets;

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

	// Timer Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_Timer> WidgetTimerClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_Timer* WidgetTimer;

	// Ammo Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_SkipCountdown> WidgetSkipCountdownClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_SkipCountdown* WidgetSkipCountdown;

	// Crosshair
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_Crosshair> WidgetCrosshairClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_Crosshair* WidgetCrosshair;

	// Wave Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_Wave> WidgetWaveClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_Wave* WidgetWave;

	// Points Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_Points> WidgetPointsClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_Points* WidgetPoints;

	// Text Notification Widget
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_CantBuild> WidgetTextNotificationClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_CantBuild* WidgetTextNotification;
};
