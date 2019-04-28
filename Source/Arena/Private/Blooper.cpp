// Fill out your copyright notice in the Description page of Project Settings.


#include "Blooper.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
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

	UMaterialInstanceDynamic * DynMat = GetMesh()->CreateDynamicMaterialInstance(0, GetMesh()->GetMaterials()[0]);
	if (DynMat && !isBlueTeam) {
		DynMat->SetVectorParameterValue("BodyColor", FLinearColor(1, .5, 0, 1));
		UE_LOG(LogTemp, Warning, TEXT("Setting bodycolor"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("not setting body colr"));
	}
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

