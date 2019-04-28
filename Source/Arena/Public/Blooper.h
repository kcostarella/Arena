// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blooper.generated.h"

UCLASS()
class ARENA_API ABlooper : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlooper();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float startHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float maxHealth;

	/** Shoot offset from my position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector ShootOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float healRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	float currentHealth;


	/** Projectile class to spawn. */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToLocation(FVector position);

	void AffectHealth(float amount);

	void Die();

	void Shoot(FVector MuzzleLocation, FRotator MuzzleRotation, FVector LaunchDirection);

};
