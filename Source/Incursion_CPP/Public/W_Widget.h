
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Widget.generated.h"

UCLASS()
class INCURSION_CPP_API UW_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
		void Initialise();

	virtual void Initialise_Implementation();
};
