
#pragma once

#include "CoreMinimal.h"
#include "W_Widget.h"
#include "W_LoseScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoseScreen_RequestRestartGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoseScreen_RequestMainMenu);

UCLASS()
class INCURSION_CPP_API UW_LoseScreen : public UW_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintCallable)
		FLoseScreen_RequestRestartGame RequestRestartGame;

	UPROPERTY(BlueprintCallable)
		FLoseScreen_RequestMainMenu RequestMainMenu;
};
