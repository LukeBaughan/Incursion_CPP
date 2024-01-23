
#pragma once

#include "CoreMinimal.h"

#include "A_Tower.h"
#include "Components/TextBlock.h"
#include "W_Widget.h"

#include "W_Store.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FW_Store_OnRequestTower, TSubclassOf<class AA_Tower>, TowerClass);

UCLASS()
class INCURSION_CPP_API UW_Store : public UW_Widget
{
	GENERATED_BODY()

public:
	virtual void Initialise_Implementation() override;

	void PlayButtonDenySound();
	void SetTextPlayerPoints(int Points);

	UPROPERTY(BlueprintCallable)
		FW_Store_OnRequestTower OnRequestTower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP UI")
		UTextBlock* TextPlayerPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP UI")
		USoundBase* ButtonDenySound;	
	
};
