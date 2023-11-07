
#pragma once

#include "CoreMinimal.h"

#include "Components/TextBlock.h"
#include "W_Widget.h"

#include "W_HUD_Points.generated.h"

UCLASS()
class INCURSION_CPP_API UW_HUD_Points : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UFUNCTION()
		void SetPoints(int Points);

	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextBlockPoints;
	
};
