
#include "W_Options.h"

void UW_Options::Initialise_Implementation()
{
	SelectedButton = TabButtonVideo;
	SelectedHorizBox = HorizBoxVideo;
	SetCurrentSettingsTab(ESettingsTab::Video);

	if(BackButton)
	{
		BackButton->Initialise();
		BackButton->SetButtonParent(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UW_Options::Initialise_Implementation:: Unable to get BackButton"));
	}
}

void UW_Options::SetCurrentSettingsTab(ESettingsTab SettingsTab)
{
	UButton* PreviousSelectedButton = nullptr;
	UHorizontalBox* PreviousSelectedHorizBox = nullptr;
	
	if(SelectedButton)
	{
		PreviousSelectedButton  = SelectedButton;
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("UW_Options::SetCurrentSettingsTab:: Unable to get SelectedButton"));
	}

	if (SelectedHorizBox)
	{
		PreviousSelectedHorizBox = SelectedHorizBox;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UW_Options::SetCurrentSettingsTab:: Unable to get SelectedHorizBox"));
	}

	switch (SettingsTab)
	{
	case ESettingsTab::Video:
		SelectedButton = TabButtonVideo;
		SelectedHorizBox = HorizBoxVideo;
		break;
	case ESettingsTab::Audio:
		SelectedButton = TabButtonAudio;
		SelectedHorizBox = HorizBoxAudio;
		break;
	case ESettingsTab::Controls:
		SelectedButton = TabButtonControls;
		SelectedHorizBox = HorizBoxControls;
		break;
	}

	//Sets the selected tab button to stay highlighted until a different tab button is pressed
	PreviousSelectedButton->WidgetStyle.SetNormal(SelectedButton->WidgetStyle.Normal);
	SelectedButton->WidgetStyle.SetNormal(SelectedButton->WidgetStyle.Hovered);

	PreviousSelectedHorizBox->SetVisibility(ESlateVisibility::Collapsed);
	SelectedHorizBox->SetVisibility(ESlateVisibility::Visible);
}