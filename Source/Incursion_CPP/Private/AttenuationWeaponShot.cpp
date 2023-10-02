// Fill out your copyright notice in the Description page of Project Settings.


#include "AttenuationWeaponShot.h"

UAttenuationWeaponShot::UAttenuationWeaponShot()
{
	Attenuation.bEnableListenerFocus = true;
	Attenuation.DistanceAlgorithm = EAttenuationDistanceModel::NaturalSound;
	Attenuation.dBAttenuationAtMax = -60.0f;
	Attenuation.AttenuationShape = EAttenuationShape::Sphere;
	Attenuation.AttenuationShapeExtents = FVector(800.0f);
	Attenuation.FalloffDistance = 4000.0f;
	Attenuation.bEnableOcclusion = true;
}