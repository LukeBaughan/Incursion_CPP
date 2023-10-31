
#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "W_HUD_Lives.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD_Lives : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

	void SetLives(int Amount);

	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockLives;
};
