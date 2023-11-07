
#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_Widget.h"

#include "W_HUD_Timer.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD_Timer : public UW_Widget
{
	GENERATED_BODY()

public:

	virtual void Initialise_Implementation() override;

	void SetCountdownTime(int Time);

	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockCountdownTime;
};
