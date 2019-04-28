// Fill out your copyright notice in the Description page of Project Settings.


#include "Blooper.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "Projectile.h"
// Sets default values
ABlooper::ABlooper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlooper::BeginPlay()
{
	Super::BeginPlay();

	currentHealth = startHealth;
}

// Called every frame
void ABlooper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentHealth += healRate * DeltaTime;
}

// Called to bind functionality to input
void ABlooper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABlooper::AffectHealth(float amount)
{
	currentHealth = FMath::Min(currentHealth + amount, maxHealth);
}

void ABlooper::Die()
{
	if (!GetMesh()->BodyInstance.bSimulatePhysics)
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->AddForce(FVector::UpVector * 10000.0F * GetMesh()->GetMass());
	}
}

void ABlooper::Shoot(FVector MuzzleLocation, FRotator MuzzleRotation, FVector LaunchDirection)
{

	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// Spawn the projectile at the muzzle.
			AProjectile* Proj = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Proj)
			{
				Proj->Owner = this;
				// Set the projectile's initial trajectory.				
				Proj->FireInDirection(LaunchDirection);
			}
		}
	}
}

