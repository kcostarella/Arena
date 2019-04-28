// Fill out your copyright notice in the Description page of Project Settings.
#include "BasicUtilityAIController.h"
#include "Food.h"
#include "EngineUtils.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"
#include "Blooper.h"


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
		else {
			UAIBlueprintHelperLibrary::SimpleMoveToActor(this, GetWorld()->GetFirstPlayerController()->GetPawn());
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
Type * ABasicUtilityAIController::GetNumberOf() const
{
	int c = 0;
	for (TActorIterator<GetterType> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		c++; //lol
	}
	return c;
	
}


