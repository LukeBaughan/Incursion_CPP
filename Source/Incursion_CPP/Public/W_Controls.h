// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "W_BackButton.h"
#include "W_Widget.h"

#include "W_Controls.generated.h"

UCLASS()
class INCURSION_CPP_API UW_Controls : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;
};
