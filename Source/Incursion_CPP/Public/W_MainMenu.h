
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BFL_Incursion.h"
#include "W_MainMenu.generated.h"

UCLASS(Abstract)
class INCURSION_CPP_API UW_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void Initialise();
};