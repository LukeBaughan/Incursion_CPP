
#pragma once

#include "CoreMinimal.h"

#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/SpinBox.h"
#include "W_BackButton.h"
#include "W_Widget.h"

#include "W_Options.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Options_RequestSetWindowMode, FString, WindowMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Options_RequestSetGraphicsQuality, FString, GraphicsQuality);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Options_RequestSetVsyncEnabled, bool, VSyncEnabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Options_RequestSetFrameRateLimit, float, FrameRateLimit);

UCLASS()
class INCURSION_CPP_API UW_Options : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UW_BackButton* BackButton;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UComboBoxString* ComboBoxWindowMode;	
	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UComboBoxString* ComboBoxGraphics;	
	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		UCheckBox* CheckBoxVsyncEnabled;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "UI")
		USpinBox* SpinBoxFrameRateLimit;

	UPROPERTY(BlueprintCallable)
		FW_Options_RequestSetWindowMode RequestSetWindowMode;

	UPROPERTY(BlueprintCallable)
		FW_Options_RequestSetGraphicsQuality RequestSetGraphicsQuality;

	UPROPERTY(BlueprintCallable)
		FW_Options_RequestSetVsyncEnabled RequestSetVsync;	
	
	UPROPERTY(BlueprintCallable)
		FW_Options_RequestSetFrameRateLimit RequestSetFrameRateLimit;
};
