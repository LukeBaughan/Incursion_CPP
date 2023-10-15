// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "W_BackButton.h"

#include "W_Credits.generated.h"

UCLASS()
class INCURSION_CPP_API UW_Credits : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;	
};
