// Fill out your copyright notice in the Description page of Project Settings.
#include "BasicUtilityAIController.h"
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
