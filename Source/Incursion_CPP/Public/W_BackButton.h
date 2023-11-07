// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BFL_Incursion.h"
#include "Blueprint/UserWidget.h"
#include "W_Widget.h"

#include "W_BackButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FButtonOnRequestOpenMenu, UW_Widget*, WOwnerMenu, MenuType, MenuToOpen);

UCLASS()
class INCURSION_CPP_API UW_BackButton : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;
	void SetButtonParent(UW_Widget* Menu);

	UPROPERTY(BlueprintReadOnly)
		UW_Widget* OwnerMenu;

	UPROPERTY(BlueprintCallable)
		FButtonOnRequestOpenMenu ButtonOnRequestOpenMenu;
};
