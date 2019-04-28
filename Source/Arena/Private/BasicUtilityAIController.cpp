// Fill out your copyright notice in the Description page of Project Settings.
#include "BasicUtilityAIController.h"
#include "Food.h"
#include "EngineUtils.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"


void ABasicUtilityAIController::BeginPlay() {
	Super::BeginPlay();
}
void ABasicUtilityAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	UAIBlueprintHelperLibrary::SimpleMoveToActor(this, GetWorld()->GetFirstPlayerController()->GetPawn());

}


void ABasicUtilityAIController::MoveToLocation(FVector position) {
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, position);
}


// TODO TEST
AFood *ABasicUtilityAIController::GetClosestFood() {
	AFood *result = nullptr;
	float distance = 100000;
	for (TActorIterator<AFood> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AFood *food = *ActorItr;
		float dist = (food->GetActorLocation() - GetPawn()->GetActorLocation()).Size();
		if (result == nullptr || dist < distance) {
			distance = dist;
			result = food;
		}
	}
	return result;
}
