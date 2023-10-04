// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Gun_Shotgun.h"

AA_Gun_Shotgun::AA_Gun_Shotgun() : AA_Gun()
{
	// Sets up the gun skeletal mesh component

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshAsset(TEXT("/Game/MilitaryWeapSilver/Weapons/Shotgun_A"));

	if (GunMeshAsset.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunMeshAsset.Object);
		UE_LOG(LogTemp, Warning, TEXT("Static mesh successfully set for AA_Gun_Shotgun."));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to set static mesh for AA_Gun_Shotgun."));
}