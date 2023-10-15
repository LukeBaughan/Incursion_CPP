// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "A_Gun.h"
#include "Engine/GameInstance.h"

#include "GI_Incursion.generated.h"

UCLASS()
class INCURSION_CPP_API UGI_Incursion : public UGameInstance
{
	GENERATED_BODY()

public:
	UGI_Incursion();

	void SetSpawnWeaponClass(TSubclassOf<class AA_Gun>  SpawnWeaponClassType);

	TSubclassOf<class AA_Gun>  GetSpawnWeaponClass();

private:

	TSubclassOf<class AA_Gun> SpawnWeaponClass;
};
