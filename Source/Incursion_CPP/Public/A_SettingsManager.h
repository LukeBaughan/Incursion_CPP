
#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/GameUserSettings.h"
#include "W_Options.h"

#include "A_SettingsManager.generated.h"

UCLASS()
class INCURSION_CPP_API AA_SettingsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_SettingsManager();
	void Initialise(UW_Options* WidgetOptionsRef);

	UFUNCTION()
		void SetWindowMode(FString WindowMode);

	UFUNCTION()
		void SetGraphicsQuality(FString GraphicsQuality);

	UFUNCTION()
		void SetVsyncEnabled(bool VsyncEnabled);	
	
	UFUNCTION()
		void SetFrameRateLimit(float FrameRateLimit);

	UW_Options* WidgetOptions;

private:
	UGameUserSettings* GameSettings;
};
