
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BFL_Incursion.h"
#include "W_Widget.h"

#include "W_MainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestQuitGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestOpenMenu, UW_Widget*, MainMenu, MenuType, MenuToOpen);

UCLASS(Abstract)
class INCURSION_CPP_API UW_MainMenu : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	UPROPERTY(BlueprintCallable)
		FOnRequestQuitGame OnRequestQuitGame;

	UPROPERTY(BlueprintCallable)
		FOnRequestOpenMenu OnRequestOpenMenu;
};