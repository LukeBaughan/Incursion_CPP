// Fill out your copyright notice in the Description page of Project Settings.

#include "A_Gun_Shotgun.h"

// Shoots multiple line traces in a filtered random directions
void AA_Gun_Shotgun::ShootLineTrace()
{
	for (int8 CurrentPellet = 0; CurrentPellet < PelletAmount; ++CurrentPellet)
	{
		FVector ShotStartLocation = PlayerCamera->GetComponentLocation();

		FVector PlayerCameraDirection = PlayerCamera->GetForwardVector();

		FVector ShotEndLocation = (FVector(PlayerCameraDirection.X + BFL_Incursion->GetAveragePelletOffset(MaxPelletOffset),
			PlayerCameraDirection.Y + BFL_Incursion->GetAveragePelletOffset(MaxPelletOffset), PlayerCameraDirection.Z + BFL_Incursion->GetAveragePelletOffset(MaxPelletOffset))
			* Range) + ShotStartLocation;

		BFL_Incursion->LineTraceShootEnemy(GetWorld(), ShotStartLocation, ShotEndLocation, Damage);
	}
}