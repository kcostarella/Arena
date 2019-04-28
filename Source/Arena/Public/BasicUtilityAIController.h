// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicUtilityAIController.generated.h"


/**
 * 
 */
UCLASS()
class ARENA_API ABasicUtilityAIController : public AAIController
{
	GENERATED_BODY()


private:

	void MoveToLocation(FVector position);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
