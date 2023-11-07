// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Controls.h"

void UW_Controls::Initialise_Implementation()
{
	BackButton->Initialise();
	BackButton->SetButtonParent(this);
}