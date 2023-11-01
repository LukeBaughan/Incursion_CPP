// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Enemy.h"

#include "A_EndGoal.h"
#include "AIC_Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AC_Enemy::AC_Enemy() :
	CapsuleCollider(GetCapsuleComponent()),
	FollowRangeCylinder(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Follow Range Cylinder"))),
	AttackRangeCylinder(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Attack Range Cylinder"))),
	BodyMesh(GetMesh()),
	MovementComponent(GetCharacterMovement()),
	IsDead(false),
	PlayerInFollowRange(false),
	PlayerInAttackRange(false),
	AttackReady(true),
	PointsAwarded(100),
	LivesCost(1),
	AttackRate(1.0f),
	MaxWalkSpeed(100.0f),
	MaxAcceleration(100.0f),
	MaxHealth(100.0f),
	CurrentHealth(0.0f),
	AttackDamage(50.0f),
	AttackAnimation(nullptr),
	AttackSound(nullptr),
	HitSound(nullptr),
	HealthBar(CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"))),
	HealthBarInterface(nullptr)
{ 
	// Collsion
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// ECC_GameTraceChannel2 = Enemy Channel
	CapsuleCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	CapsuleCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);



	// Follow Range Cylinder - Only Interacts with the player
	FollowRangeCylinder->SetupAttachment(CapsuleCollider);
	FollowRangeCylinder->SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector));
	FollowRangeCylinder->bHiddenInGame = true;
	FollowRangeCylinder->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FollowRangeCylinder->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	FollowRangeCylinder->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// ECC_GameTraceChannel2 = Player Channel
	FollowRangeCylinder->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Overlap);



	// Attack Range Cylinder - Only Interacts with the player
	AttackRangeCylinder->SetupAttachment(CapsuleCollider);
	AttackRangeCylinder->SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector));
	AttackRangeCylinder->bHiddenInGame = true;
	AttackRangeCylinder->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AttackRangeCylinder->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	AttackRangeCylinder->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// ECC_GameTraceChannel2 = Player Channel
	AttackRangeCylinder->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Overlap);



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

void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();

	// Collision Event Bindings

	CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &AC_Enemy::CapsuleColliderOnOverlapBegin);

	FollowRangeCylinder->OnComponentBeginOverlap.AddDynamic(this, &AC_Enemy::FollowRangeCylinderOnOverlapBegin);
	FollowRangeCylinder->OnComponentEndOverlap.AddDynamic(this, &AC_Enemy::FollowRangeCylinderOnOverlapEnd);

	AttackRangeCylinder->OnComponentBeginOverlap.AddDynamic(this, &AC_Enemy::AttackRangeCylinderOnOverlapBegin);
	AttackRangeCylinder->OnComponentEndOverlap.AddDynamic(this, &AC_Enemy::AttackRangeCylinderOnOverlapEnd);
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
			// Continue when starting store manager
			OnDefeated.Broadcast(this, PointsAwarded);

			CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			MovementComponent->DisableMovement();
			HealthBar->SetVisibility(false, false);

			// Plays an random animation when defeated				
			if (DeathAnimations.Num() > 0)
			{
				BodyMesh->PlayAnimation(DeathAnimations[FMath::RandRange(0, DeathAnimations.Num() - 1)], false);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("C_Enemy: Unable to get DeathAnimation"));
			}
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

void AC_Enemy::CapsuleColliderOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AA_EndGoal* EndGoal = Cast<AA_EndGoal>(OtherActor);

	if (EndGoal)
	{	
		OnGoalReached.Broadcast(LivesCost);
		DestroySelf();
	}
}

void AC_Enemy::FollowRangeCylinderOnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsDead)
	{
		PlayerInFollowRange = true;
	}
}

void AC_Enemy::FollowRangeCylinderOnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerInFollowRange = false;
}

void AC_Enemy::AttackRangeCylinderOnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsDead)
	{
		PlayerInAttackRange = true;
	}
}

void AC_Enemy::AttackRangeCylinderOnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerInAttackRange = false;
}

bool AC_Enemy::GetPlayerInFollowRange()
{	
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("%s"), PlayerInFollowRange ? TEXT("true") : TEXT("false")));
	return PlayerInFollowRange;
}

bool AC_Enemy::GetPlayerInAttackRange()
{	
	return PlayerInAttackRange;
}

bool AC_Enemy::GetAttackReady()
{	
	return AttackReady;
}

float AC_Enemy::GetAttackDamage()
{
	return AttackDamage;
}

void AC_Enemy::OnAttackExecuted()
{
	AttackReady = false;
	GetWorldTimerManager().SetTimer(TH_AttackCooldown, this, &AC_Enemy::EndAttackCooldown, AttackRate, false);
}

void AC_Enemy::EndAttackCooldown()
{
	GetWorldTimerManager().ClearTimer(TH_AttackCooldown);
	AttackReady = true;
}

USkeletalMeshComponent* AC_Enemy::GetBodyMesh()
{
	return BodyMesh;
}

USoundBase* AC_Enemy::GetAttackSound()
{
	return AttackSound;
}

UAnimMontage* AC_Enemy::GetAttackAnimation()
{
	return AttackAnimation;
}