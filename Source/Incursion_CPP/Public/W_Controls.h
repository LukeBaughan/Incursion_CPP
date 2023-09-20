// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_BackButton.h"
#include "W_Controls.generated.h"

/**
 * 
 */
UCLASS()
class INCURSION_CPP_API UW_Controls : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;

	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

};
