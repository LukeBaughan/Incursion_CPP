
#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "W_HUD_Timer.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD_Timer : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

	void SetCountdownTime(int Time);

	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockCountdownTime;
};
