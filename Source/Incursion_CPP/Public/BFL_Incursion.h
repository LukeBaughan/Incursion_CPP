// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Button.h"
#include "BFL_Incursion.generated.h"

/**
 * 
 */
UCLASS()
class INCURSION_CPP_API UBFL_Incursion : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI Design")
	static void SetUpButtonColours(TArray<UButton*> Buttons);
};
