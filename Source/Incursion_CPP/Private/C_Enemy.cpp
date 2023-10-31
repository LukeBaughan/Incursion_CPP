// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Enemy.h"

#include "A_EndGoal.h"
#include "AIC_Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AC_Enemy::AC_Enemy() :
	CapsuleCollider(GetCapsuleComponent()),
	BodyMesh(GetMesh()),
	MovementComponent(GetCharacterMovement()),
	IsDead(false),
	PointsAwarded(100),
	LivesCost(1),
	MaxWalkSpeed(100.0f),
	MaxAcceleration(100.0f),
	MaxHealth(100.0f),
	CurrentHealth(0.0f),
	HitSound(nullptr),
	HealthBar(CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"))),
	HealthBarInterface(nullptr)
{ 
	// Collsion
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// ECC_GameTraceChannel2 = Enemy Channel
	CapsuleCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	CapsuleCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);

	CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &AC_Enemy::OnOverlapBegin);

	// Smooth Rotation
	bUseControllerRotationYaw = false;
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->bUseControllerDesiredRotation = false;

	BodyMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BodyMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	BodyMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	BodyMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	BodyMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	BodyMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);

	HealthBar->SetupAttachment(CapsuleCollider);
	HealthBar->SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector));
}

void AC_Enemy::Initialise()
{	
	// Sets up Stats
	MovementComponent->MaxWalkSpeed = MaxWalkSpeed;
	MovementComponent->MaxAcceleration = MaxAcceleration;
	CurrentHealth = MaxHealth;

	HealthBarInterface = Cast<II_HealthBar>(HealthBar->GetWidget());
	if (HealthBarInterface)
	{
		HealthBarInterface->InitialiseWidget();
	}
}

void AC_Enemy::TakeDamageCharacter(float DamageAmount)
{
	if (!IsDead)
	{
		UGameplayStatics::SpawnSoundAttached(HitSound, BodyMesh);
		// Loses health when recieving damage
		CurrentHealth -= DamageAmount;
		UpdateHealthBar();
		// If they have no health left, they die
		if (CurrentHealth <= 0)
		{
			IsDead = true;
			// TEMPORARY
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("C_Enemy: %d Points Awarded"), PointsAwarded));
			DestroySelf();
		}
	}
}

void AC_Enemy::UpdateHealthBar()
{
	if (HealthBarInterface)
	{
		HealthBarInterface->SetHealth(CurrentHealth, MaxHealth);
	}
}

void AC_Enemy::DestroySelf()
{
	GetController()->Destroy();
	this->Destroy();
}

void AC_Enemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AA_EndGoal* EndGoal = Cast<AA_EndGoal>(OtherActor);

	if (EndGoal)
	{	
		OnGoalReached.Broadcast(LivesCost);
		DestroySelf();
	}
}