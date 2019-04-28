// Fill out your copyright notice in the Description page of Project Settings.
#include "BasicUtilityAIController.h"
#include "Food.h"
#include "EngineUtils.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"
#include "Blooper.h"
#include "Components/SkeletalMeshComponent.h"

void ABasicUtilityAIController::BeginPlay() {
	Super::BeginPlay();
	ControlledBlooper = Cast<ABlooper>(GetPawn());
	if (!ControlledBlooper)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Controlled Blooper for this guy"));
	}
}
void ABasicUtilityAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	if (ControlledBlooper->currentHealth > 0)
	{
		AFood * ClosestFood = GetClosestFood();
		if (ControlledBlooper->currentHealth < 50 && ClosestFood)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,ClosestFood->GetActorLocation());

		}
		else 
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(this, GetWorld()->GetFirstPlayerController()->GetPawn());
		}

		if (GetWorld()->GetRealTimeSeconds() > LastFire + FireRate)
		{
			//fire at the player
			FireAtEnemyBlooper();
		}
	} 
	else
	{
		StopMovement();
		ControlledBlooper->Die();
	}

}


void ABasicUtilityAIController::MoveToLocation(FVector position) {
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, position);
}

void ABasicUtilityAIController::FireAtEnemyBlooper()
{
	ABlooper * closestBloop = GetClosestEnemyBlooper(); //could just be player

										 // Transform MuzzleOffset from camera space to world space.
	FVector MuzzleLocation = ControlledBlooper->GetMesh()->GetSocketLocation("headSocket");
	FRotator MuzzleRotation = ControlledBlooper->GetMesh()->GetSocketRotation("headSocket");
	MuzzleRotation.Pitch += 20.0f;
	FVector Direction = (closestBloop->GetActorLocation() - MuzzleLocation).GetSafeNormal();
	ControlledBlooper->Shoot(MuzzleLocation, MuzzleRotation, Direction);
	LastFire = GetWorld()->GetRealTimeSeconds();
}



// TODO TEST
AFood *ABasicUtilityAIController::GetClosestFood() {
	return GetClosest<AFood>();
}

ABlooper * ABasicUtilityAIController::GetClosestEnemyBlooper()
{
	return GetClosest<ABlooper>();
}

template<class GetterType>
GetterType * ABasicUtilityAIController::GetClosest() const
{
	GetterType *result = nullptr;
	float distance = 100000;
	for (TActorIterator<GetterType> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		GetterType *t = *ActorItr;
		float dist = (t->GetActorLocation() - GetPawn()->GetActorLocation()).Size();
		if (result == nullptr || dist < distance) {
			distance = dist;
			result = t;
		}
	}
	return result;
}


template<class Type>
int ABasicUtilityAIController::GetNumberOf() const
{
	int c = 0;
	for (TActorIterator<GetterType> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		c++; //lol
	}
	return c;
	
}


