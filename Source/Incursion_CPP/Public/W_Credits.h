// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "W_BackButton.h"
#include "W_Widget.h"

#include "W_Credits.generated.h"

UCLASS()
class INCURSION_CPP_API UW_Credits : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;	
};
