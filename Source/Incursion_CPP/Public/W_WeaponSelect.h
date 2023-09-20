// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_BackButton.h"
#include "W_WeaponSelect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponSelected);

UCLASS()
class INCURSION_CPP_API UW_WeaponSelect : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;

	UPROPERTY(BlueprintCallable)
		FOnWeaponSelected OnWeaponSelected;

	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

	
};
