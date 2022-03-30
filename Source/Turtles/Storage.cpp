// Fill out your copyright notice in the Description page of Project Settings.


#include "Storage.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

AStorage* STORAGE = nullptr;

void AStorage::create(UWorld* world) {
	if (world != nullptr) {
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto storage = world->SpawnActor<AStorage>(AStorage::StaticClass(), FVector(0), FRotator(0), ActorSpawnParams);
		check(storage != nullptr);

		STORAGE = storage;

		storage->initialize();
	}
}

void AStorage::initialize() {
	TrionixBody = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Models/trionix")));
	check(TrionixBody != nullptr);

	UE_LOG(LogTemp, Warning, TEXT("AStorage initialized"));
}

AStorage& AStorage::GetStorage(UWorld* world) {
	if (STORAGE == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("AStorage not found -- create it and load models"));
		check(world != nullptr);

		AStorage::create(world);
		check(STORAGE != nullptr);
	}

	return *STORAGE;
}

AStorage::AStorage()
{
	UE_LOG(LogTemp, Warning, TEXT("AStorage constructor"));
}

AStorage::~AStorage()
{
	UE_LOG(LogTemp, Warning, TEXT("AStorage destructor"));
}