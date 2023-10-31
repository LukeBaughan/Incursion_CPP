// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	// Ammo Counter
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UW_HUD_Ammo> WidgetAmmoClass;
	UPROPERTY(BlueprintReadWrite)
		class UW_HUD_Ammo* WidgetAmmo;
};
