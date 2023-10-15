
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BFL_Incursion.h"

#include "W_MainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestQuitGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestOpenMenu, UUserWidget*, MainMenu, MenuType, MenuToOpen);

UCLASS(Abstract)
class INCURSION_CPP_API UW_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Initialise();

	UPROPERTY(BlueprintCallable)
	FOnRequestQuitGame OnRequestQuitGame;

	UPROPERTY(BlueprintCallable)
	FOnRequestOpenMenu OnRequestOpenMenu;
};