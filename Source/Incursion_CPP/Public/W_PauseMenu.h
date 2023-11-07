
#pragma once

#include "CoreMinimal.h"

#include "BFL_Incursion.h"
#include "Blueprint/UserWidget.h"
#include "W_Widget.h"

#include "W_PauseMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPauseMenuOnRequestOpenMenu, UW_Widget*, PauseMenu, MenuType, MenuToOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseMenu_RequestTogglePause, bool, Pause);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseMenu_RequestMainMenu);


UCLASS()
class INCURSION_CPP_API UW_PauseMenu : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UPROPERTY(BlueprintCallable)
		FPauseMenuOnRequestOpenMenu OnRequestOpenMenu;

	UPROPERTY(BlueprintCallable)
		FPauseMenu_RequestTogglePause RequestTogglePause;

	UPROPERTY(BlueprintCallable)
		FPauseMenu_RequestMainMenu RequestMainMenu;
};
