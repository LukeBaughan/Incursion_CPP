// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_Widget.h"

#include "W_HUD_Ammo.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD_Ammo : public UW_Widget
{
	GENERATED_BODY()

public:

	virtual void Initialise_Implementation() override;

	UFUNCTION()
		void SetAmmoAmount(int8 CurrentAmmo, int8 MaxAmmo);

	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockAmmo;
};
