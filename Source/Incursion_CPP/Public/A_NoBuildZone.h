
#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "A_NoBuildZone.generated.h"

UCLASS()
class INCURSION_CPP_API AA_NoBuildZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_NoBuildZone();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UBoxComponent* BoxCollider;

protected:
	virtual void BeginPlay() override;
};
