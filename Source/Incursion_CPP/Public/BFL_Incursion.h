// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AttenuationWeaponShot.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "W_Widget.h"

#include "BFL_Incursion.generated.h"

UCLASS()
class INCURSION_CPP_API UBFL_Incursion : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	static void SetUpButtonColours(TArray<UButton*> Buttons);

	UFUNCTION(BlueprintCallable, Category = "UI")
	static void OpenMenu(UW_Widget* CurrentMenu, UW_Widget* MenuToOpen);

	void SetHealthBarAmount(UProgressBar* HealthBar, float CurrentHealth, float MaxHealth);

	FVector LineTraceShootEnemy(UWorld* WorldObject, FVector StartLocation, FVector EndLocation, float Damage, USoundBase* ShootSound = nullptr);

	float GetAveragePelletOffset(float MaxOffset);

private:

	UAttenuationWeaponShot* AttWeaponShot;
};

UENUM(BlueprintType)
enum MenuType
{
	Main UMETA(DisplayName = "Main"),
	Options UMETA(DisplayName = "Options"),
	Statistics UMETA(DisplayName = "Stats"),
	Controls UMETA(DisplayName = "Controls"),
	Credits UMETA(DisplayName = "Credits"),
	WeaponSelect UMETA(DisplayName = "WeaponSelect"),
	Win UMETA(DisplayName = "Win"),
	Lose UMETA(DisplayName = "Lose")
};
