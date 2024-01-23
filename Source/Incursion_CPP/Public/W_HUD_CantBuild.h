
/// CAN BE USED FOR ANY UI NOTIFICATION, NOT JUST CANT BUILD ////

#pragma once

#include "CoreMinimal.h"
#include "W_Widget.h"
#include "W_HUD_CantBuild.generated.h"

UENUM()
enum class ENotificationTextType : uint8
{
	CantPlace,
	CantAfford
};

UCLASS()
class INCURSION_CPP_API UW_HUD_CantBuild : public UW_Widget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP UI")
		FString CantPlaceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP UI")
		FString CantAffordText;
	
};
