
#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

#include "A_SpectatorCamera.generated.h"

UCLASS()
class INCURSION_CPP_API AA_SpectatorCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_SpectatorCamera();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BP Assets")
		UCameraComponent* CameraComponent;
};
