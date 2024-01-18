
#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/GameUserSettings.h"
#include "SG_Incursion.h"
#include "W_Options.h"

#include "A_SettingsManager.generated.h"

UCLASS()
class INCURSION_CPP_API AA_SettingsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_SettingsManager();
	void Initialise(UW_Options* WidgetOptionsRef);

	// Video

	UFUNCTION()
		void SetWindowMode(FString WindowMode);

	UFUNCTION()
		void SetGraphicsQuality(FString GraphicsQuality);

	UFUNCTION()
		void SetVsyncEnabled(bool VsyncEnabled);	
	
	UFUNCTION()
		void SetFrameRateLimit(float FrameRateLimit);

	// Audio

	UFUNCTION()
		void SetVolume(EAudioClassType AudioClass, float VolumeAmount);

	USG_Incursion* SaveGameIncursion;
	FString SaveFileName;
	UW_Options* WidgetOptions;

private:
	UGameUserSettings* GameSettings;

	USoundMix* IncursionSoundClassMix;
	TArray<USoundClass*> IncursionSoundClasses;
};
