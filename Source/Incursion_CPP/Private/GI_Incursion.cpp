// Fill out your copyright notice in the Description page of Project Settings.

#include "GI_Incursion.h"

UGI_Incursion::UGI_Incursion() :
	SpawnWeaponClass(NULL)
{
}

void UGI_Incursion::SetSpawnWeaponClass(TSubclassOf<class AA_Gun>  SpawnWeaponClassType)
{
	SpawnWeaponClass = SpawnWeaponClassType;
}

TSubclassOf<class AA_Gun>  UGI_Incursion::GetSpawnWeaponClass()
{
	return SpawnWeaponClass;
}