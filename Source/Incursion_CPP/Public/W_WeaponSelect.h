// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "A_Gun.h"
#include "Blueprint/UserWidget.h"
#include "W_BackButton.h"

#include "W_WeaponSelect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponSelected, TSubclassOf<class AA_Gun>, WeaponClass);

UCLASS()
class INCURSION_CPP_API UW_WeaponSelect : public UUserWidget
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;

	UPROPERTY(BlueprintCallable)
		FOnWeaponSelected OnWeaponSelected;
};
