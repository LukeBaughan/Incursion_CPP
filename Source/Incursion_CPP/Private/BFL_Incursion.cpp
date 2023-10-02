// Fill out your copyright notice in the Description page of Project Settings.

#include "BFL_Incursion.h"
#include "Math/Color.h"
#include "Styling/SlateBrush.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h" 

void UBFL_Incursion::SetUpButtonColours(TArray<UButton*> Buttons)
{
	FSlateColor NewButtonColour = FSlateColor(FLinearColor(0.023529f, 0.023529f, 0.027451f));
	FSlateColor NewButtonHoverColour = FSlateColor(FLinearColor(0.109804f, 0.109804f, 0.129412f));

	for (UButton* Button : Buttons)
	{
		// Copies over the style of the current button and then changes the colour style to the new style
		FButtonStyle NewButtonStyle = Button->WidgetStyle;

		// Button Colour
		NewButtonStyle.Normal.TintColor = NewButtonColour;
		// Box = No border around the button
		NewButtonStyle.Normal.DrawAs = ESlateBrushDrawType::Box;

		NewButtonStyle.Pressed.TintColor = NewButtonColour;
		NewButtonStyle.Pressed.DrawAs = ESlateBrushDrawType::Box;

		NewButtonStyle.Disabled.TintColor = NewButtonColour;
		NewButtonStyle.Disabled.DrawAs = ESlateBrushDrawType::Box;

		NewButtonStyle.Hovered.TintColor = NewButtonHoverColour;
		NewButtonStyle.Hovered.DrawAs = ESlateBrushDrawType::Box;

		// Sets the button's style to be the new style
		Button->SetStyle(NewButtonStyle);
	}
}

void UBFL_Incursion::OpenMenu(UUserWidget* CurrentMenu, UUserWidget* MenuToOpen)
{
	// Hides the current menu and displays the requested menu
	CurrentMenu->SetVisibility(ESlateVisibility::Collapsed);
	MenuToOpen->SetVisibility(ESlateVisibility::Visible);
}

// Performs a line trace and damages the first enemy if hit
FVector UBFL_Incursion::LineTraceShootEnemy(UWorld* WorldObject, FVector StartLocation, FVector EndLocation, float Damage, USoundBase* ShootSound)
{
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionParameters;

	// ECC_GameTraceChannel2 = Enemy Collision Object Channel
	CollisionParameters.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

	if(ShootSound)
		UGameplayStatics::PlaySoundAtLocation(WorldObject, ShootSound, StartLocation, 1.0f, 1.0f, 0.0f, AttWeaponShot);

	bool LineTrace = WorldObject->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, CollisionParameters);


	// Debug Line
	DrawDebugLine(WorldObject, StartLocation, EndLocation, FColor::Red, false, 3.0f, 0, 2.0f);

	return HitResult.Location;
}