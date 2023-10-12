// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_Player_Base.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadFinishedAnimInst);

UCLASS()
class INCURSION_CPP_API UAnimInst_Player_Base : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAnimInst_Player_Base();

	UPROPERTY(BlueprintCallable)
		FOnReloadFinishedAnimInst OnReloadFinishedAnimInst;

	UPROPERTY(BlueprintReadOnly)
		bool CurrentlyShooting;	
	
	UPROPERTY(BlueprintReadWrite)
		bool CurrentlyReloading;
};
