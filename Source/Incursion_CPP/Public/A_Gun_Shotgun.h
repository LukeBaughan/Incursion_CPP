// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_Gun.h"
#include "A_Gun_Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class INCURSION_CPP_API AA_Gun_Shotgun : public AA_Gun
{
	GENERATED_BODY()
	
public:
	AA_Gun_Shotgun();

protected:
	virtual void ShootLineTrace() override;

private:
	int8 PelletAmount;
	float MaxPelletOffset;

};
