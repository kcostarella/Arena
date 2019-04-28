// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Blooper.h"
// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::OnPickup(AActor * CollisionActor) 
{
	UE_LOG(LogTemp, Warning, TEXT("On Pickup happened with %s"), *CollisionActor->GetName());
	ABlooper * BlooperActor = Cast<ABlooper>(CollisionActor);
	if (BlooperActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blooper hit, going away!"));
		BlooperActor->AffectHealth(10.0F);
		Destroy();
	}
}

