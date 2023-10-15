// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BFL_Incursion.h"
#include "Blueprint/UserWidget.h"

#include "W_BackButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FButtonOnRequestOpenMenu, UUserWidget*, WOwnerMenu, MenuType, MenuToOpen);


UCLASS()
class INCURSION_CPP_API UW_BackButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
		void Initialise(UUserWidget* WidgetOwnerMenu);

	UPROPERTY(BlueprintReadOnly)
		UUserWidget* OwnerMenu;

	UPROPERTY(BlueprintCallable)
		FButtonOnRequestOpenMenu ButtonOnRequestOpenMenu;
};
