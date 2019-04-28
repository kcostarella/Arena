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



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float healRate;


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

private:
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	float currentHealth;

};
