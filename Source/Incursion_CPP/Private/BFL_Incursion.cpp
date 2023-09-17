// Fill out your copyright notice in the Description page of Project Settings.

#include "BFL_Incursion.h"
#include "Math/Color.h"
#include "Styling/SlateBrush.h"

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