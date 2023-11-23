
#pragma once

#include "CoreMinimal.h"
#include "W_Widget.h"
#include "W_WinScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinScreen_RequestRestartGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinScreen_RequestMainMenu);

UCLASS()
class INCURSION_CPP_API UW_WinScreen : public UW_Widget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintCallable)
		FWinScreen_RequestRestartGame RequestRestartGame;

	UPROPERTY(BlueprintCallable)
		FWinScreen_RequestMainMenu RequestMainMenu;
};
