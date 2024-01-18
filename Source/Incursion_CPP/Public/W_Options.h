
#pragma once

#include "CoreMinimal.h"

#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/HorizontalBox.h"
#include "Components/SpinBox.h"
#include "W_BackButton.h"
#include "W_Widget.h"

#include "W_Options.generated.h"

UENUM(BlueprintType)
enum class ESettingsTab : uint8
{
	Video,
	Audio,
	Controls
};

UENUM(BlueprintType)
enum class EAudioClassType : uint8
{
	Master,
	Music,
	SFX
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Options_RequestSetWindowMode, FString, WindowMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Options_RequestSetGraphicsQuality, FString, GraphicsQuality);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Options_RequestSetVsyncEnabled, bool, VSyncEnabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Options_RequestSetFrameRateLimit, float, FrameRateLimit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FW_Options_RequestSetVolume, EAudioClassType, AudioClass, float, VolumeAmount);


UCLASS()
class INCURSION_CPP_API UW_Options : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
		void SetCurrentSettingsTab(ESettingsTab SettingsTab);
	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UButton* TabButtonVideo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UButton* TabButtonAudio;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UButton* TabButtonControls;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Video")
		UHorizontalBox* HorizBoxVideo;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI Video")
		UComboBoxString* ComboBoxWindowMode;	
	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI Video")
		UComboBoxString* ComboBoxGraphics;	
	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI Video")
		UCheckBox* CheckBoxVsyncEnabled;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI Video")
		USpinBox* SpinBoxFrameRateLimit;

	UPROPERTY(BlueprintCallable, Category = "UI Video")
		FW_Options_RequestSetWindowMode RequestSetWindowMode;

	UPROPERTY(BlueprintCallable, Category = "UI Video")
		FW_Options_RequestSetGraphicsQuality RequestSetGraphicsQuality;

	UPROPERTY(BlueprintCallable, Category = "UI Video")
		FW_Options_RequestSetVsyncEnabled RequestSetVsync;	
	
	UPROPERTY(BlueprintCallable, Category = "UI Video")
		FW_Options_RequestSetFrameRateLimit RequestSetFrameRateLimit;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Audio")
		UHorizontalBox* HorizBoxAudio;

	UPROPERTY(BlueprintCallable, Category = "UI Audio")
		FW_Options_RequestSetVolume RequestSetVolume;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Audio")
		USoundMix* IncursionSoundClassMix;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Audio")
		TArray<USoundClass*> SoundClasses;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Audio")
		TArray<USpinBox*> VolumeSliders;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Controls")
		UHorizontalBox* HorizBoxControls;

private:

	UButton* SelectedButton;
	UHorizontalBox* SelectedHorizBox;
};
