// Fill out your copyright notice in the Description page of Project Settings.


#include "Cave.h"

// Sets default values
ACave::ACave()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* BodyMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Models/cave")));
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	auto Result = Body->SetStaticMesh(BodyMesh);
	check(Result != false);

	RootComponent = Body;
	SpawnInterval = 0;

	Body->SetMobility(EComponentMobility::Type::Movable);

}

UWorld& ACave::get_world() {
	auto World = GetWorld();
	check(World != nullptr);

	return *World;
}

// Called when the game starts or when spawned
void ACave::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnInterval > 0) {
		SpawnInterval -= DeltaTime;

		if (SpawnInterval < 0.0) {
			SpawnInterval = 0;
		}
	}
}

void ACave::SpawnTurtle() {
	if (SpawnInterval == 0) {
		SpawnInterval = SPAWN_INTERVAL;

		if (Turtle != nullptr) {
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			auto turtle = get_world().SpawnActor<ATurtle>(Turtle, GetActorLocation(), GetActorRotation(), ActorSpawnParams);
			turtle->SetDestination(Destination);
		}
	}
}
