
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Enemy.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_Enemy : public UInterface
{
	GENERATED_BODY()
};

class INCURSION_CPP_API II_Enemy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool GetPlayerInFollowRange();
	virtual bool GetPlayerInAttackRange();
	virtual bool GetAttackReady();
	virtual float GetAttackDamage();
	virtual void OnAttackExecuted();
	virtual USkeletalMeshComponent* GetBodyMesh();
	virtual USoundBase* GetAttackSound();
	virtual UAnimMontage* GetAttackAnimation();

};
