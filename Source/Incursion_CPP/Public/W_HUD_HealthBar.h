
#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "BFL_Incursion.h"
#include "W_Widget.h"

#include "W_HUD_HealthBar.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD_HealthBar : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UFUNCTION()
		void SetHealthBarAmount(float CurrentHealth, float MaxHealth);

	UPROPERTY(BlueprintReadWrite)
		UProgressBar* HealthBar;

private:
	UBFL_Incursion* BFL_Incursion;
};
