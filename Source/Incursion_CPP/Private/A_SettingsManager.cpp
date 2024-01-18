
#include "A_SettingsManager.h"

#include "Kismet/GameplayStatics.h"

AA_SettingsManager::AA_SettingsManager() :
	SaveGameIncursion(nullptr),
	SaveFileName("Incursion Save File"),
	WidgetOptions(nullptr),
	GameSettings(nullptr)
{

}

void AA_SettingsManager::Initialise(UW_Options* WidgetOptionsRef)
{
	// Loads the save game file
	USaveGame* LoadedSaveGame = UGameplayStatics::LoadGameFromSlot(SaveFileName, 0);

	if (IsValid(LoadedSaveGame))
	{
		SaveGameIncursion = Cast<USG_Incursion>(LoadedSaveGame);
	}
	// If there is no save game, create it
	else
	{
		SaveGameIncursion = Cast<USG_Incursion>(UGameplayStatics::CreateSaveGameObject(USG_Incursion::StaticClass()));
	}

	WidgetOptions = WidgetOptionsRef;
	GameSettings = UGameUserSettings::GetGameUserSettings();

	WidgetOptions->RequestSetWindowMode.AddDynamic(this, &AA_SettingsManager::SetWindowMode);
	WidgetOptions->RequestSetGraphicsQuality.AddDynamic(this, &AA_SettingsManager::SetGraphicsQuality);
	WidgetOptions->RequestSetVsync.AddDynamic(this, &AA_SettingsManager::SetVsyncEnabled);
	WidgetOptions->RequestSetFrameRateLimit.AddDynamic(this, &AA_SettingsManager::SetFrameRateLimit);

	if (WidgetOptions->ComboBoxWindowMode)
	{
		switch (GameSettings->GetFullscreenMode())
		{
		case EWindowMode::Fullscreen:
			WidgetOptions->ComboBoxWindowMode->SetSelectedOption("Fullscreen");
			break;
		case EWindowMode::WindowedFullscreen:
			WidgetOptions->ComboBoxWindowMode->SetSelectedOption("Windowed Fullscreen");
			break;
		case EWindowMode::Windowed:
			WidgetOptions->ComboBoxWindowMode->SetSelectedOption("Windowed");
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, (TEXT("AA_SettingsManager: Unable to get WidgetOptions->ComboBoxWindowMode")));
	}

	if (WidgetOptions->ComboBoxGraphics)
	{
		switch (GameSettings->GetOverallScalabilityLevel())
		{
		case 0:
			WidgetOptions->ComboBoxGraphics->SetSelectedOption("LOW");
			break;
		case 1:
			WidgetOptions->ComboBoxGraphics->SetSelectedOption("MEDIUM");
			break;
		case 2:
			WidgetOptions->ComboBoxGraphics->SetSelectedOption("HIGH");
			break;
		case 3:
			WidgetOptions->ComboBoxGraphics->SetSelectedOption("VERY HIGH");
			break;
		case 4:
			WidgetOptions->ComboBoxGraphics->SetSelectedOption("ULTRA");
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, (TEXT("AA_SettingsManager: Unable to get WidgetOptions->ComboBoxGraphics")));
	}

	if (WidgetOptions->CheckBoxVsyncEnabled)
	{
		if (GameSettings->IsVSyncEnabled())
		{
			WidgetOptions->CheckBoxVsyncEnabled->SetCheckedState(ECheckBoxState::Checked);
		}
		else
		{			
			WidgetOptions->CheckBoxVsyncEnabled->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, (TEXT("AA_SettingsManager: Unable to get WidgetOptions->CheckBoxVsyncEnabled")));
	}

	if (WidgetOptions->SpinBoxFrameRateLimit)
	{
		WidgetOptions->SpinBoxFrameRateLimit->SetValue(GameSettings->GetFrameRateLimit());
	}
	else
	{
		UE_LOG(LogTemp, Error, (TEXT("AA_SettingsManager: Unable to get WidgetOptions->SpinBoxFrameRateLimit")));
	}


	// Audio


	IncursionSoundClassMix = WidgetOptions->IncursionSoundClassMix;
	IncursionSoundClasses = WidgetOptions->SoundClasses;

	WidgetOptions->RequestSetVolume.AddDynamic(this, &AA_SettingsManager::SetVolume);

	uint8 SoundClassIndex = 0;

	for (USoundClass* SoundClass : IncursionSoundClasses)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), IncursionSoundClassMix, SoundClass, SaveGameIncursion->SoundClassVolumes[SoundClassIndex]);
		WidgetOptions->VolumeSliders[SoundClassIndex]->SetValue(SaveGameIncursion->SoundClassVolumes[SoundClassIndex] * 100);

		SoundClassIndex++;
	}
}


// Video Settings


void AA_SettingsManager::SetWindowMode(FString WindowMode)
{
	if (WindowMode == "Fullscreen")
	{
		GameSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	}
	else if (WindowMode == "Windowed Fullscreen")
	{
		GameSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	}
	else if (WindowMode == "Windowed")
	{
		GameSettings->SetFullscreenMode(EWindowMode::Windowed);
	}

	GameSettings->ApplySettings(true);
}

void AA_SettingsManager::SetGraphicsQuality(FString GraphicsQuality)
{
	if (GraphicsQuality == "LOW")
	{
		GameSettings->SetOverallScalabilityLevel(0);
	}
	else if (GraphicsQuality == "MEDIUM")
	{
		GameSettings->SetOverallScalabilityLevel(1);
	}
	else if (GraphicsQuality == "HIGH")
	{
		GameSettings->SetOverallScalabilityLevel(2);
	}
	else if (GraphicsQuality == "VERY HIGH")
	{
		GameSettings->SetOverallScalabilityLevel(3);
	}
	else if (GraphicsQuality == "ULTRA")
	{
		GameSettings->SetOverallScalabilityLevel(4);
	}

	GameSettings->ApplySettings(true);
}

void AA_SettingsManager::SetVsyncEnabled(bool VsyncEnabled)
{
	GameSettings->SetVSyncEnabled(VsyncEnabled);
	GameSettings->ApplySettings(true);
}

void AA_SettingsManager::SetFrameRateLimit(float FrameRateLimit)
{
	GameSettings->SetFrameRateLimit(FrameRateLimit);
	GameSettings->ApplySettings(true);
}


// Audio Settings

void AA_SettingsManager::SetVolume(EAudioClassType AudioClass, float VolumeAmount)
{
	VolumeAmount *= 0.01;
	// In UE5 Enums dont always equal ints, so we have to set it as an int before using it
	uint8 AudioClassTypeInt = (uint8)AudioClass;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), IncursionSoundClassMix, IncursionSoundClasses[AudioClassTypeInt], VolumeAmount);

	SaveGameIncursion->SoundClassVolumes[AudioClassTypeInt] = VolumeAmount;
	UGameplayStatics::AsyncSaveGameToSlot(SaveGameIncursion, SaveFileName, 0);
}