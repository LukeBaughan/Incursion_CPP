
#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "W_HUD_HealthBar.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD_HealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

	UFUNCTION()
		void SetHealthBarAmount(float CurrentHealth, float MaxHealth);

	UPROPERTY(BlueprintReadWrite)
		UProgressBar* HealthBar;

private:
	UBFL_Incursion* BFL_Incursion;
};
