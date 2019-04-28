// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Food.h"
#include "BasicUtilityAIController.generated.h"

class ABlooper;


/**
 * 
 */
UCLASS()
class ARENA_API ABasicUtilityAIController : public AAIController
{
	GENERATED_BODY()


private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	template<class GetterType>
	GetterType * GetClosest() const;

	template<class Type>
	int GetNumberOf() const;

	void MoveToLocation(FVector position);
	
	AFood *GetClosestFood();

	ABlooper * GetClosestEnemyBlooper();

	ABlooper * ControlledBlooper;
	
	float LastFire;

	UPROPERTY(EditAnywhere)
	float FireRate = 5.0F;

	void FireAtEnemyBlooper();

};
