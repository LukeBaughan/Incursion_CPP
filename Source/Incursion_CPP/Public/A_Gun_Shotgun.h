// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_Gun.h"
#include "A_Gun_Shotgun.generated.h"

UCLASS()
class INCURSION_CPP_API AA_Gun_Shotgun : public AA_Gun
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		uint8 PelletAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Stats")
		float MaxPelletOffset;

protected:
	virtual void ShootLineTrace() override;
};
