// Fill out your copyright notice in the Description page of Project Settings.


#include "Storage.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStorage* STORAGE;

//TODO finalize, get

void AStorage::create(UWorld* world) {
	//TODO we need set path on initialization
	//FString AbsoluteFilePath = FPaths::GameDir();

	//MY_LOG(LogTemp, Warning, TEXT("AbsoluteFilePath %s"), *AbsoluteFilePath);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto storage = world->SpawnActor<AStorage>(AStorage::StaticClass(), FVector(0), FRotator(0), ActorSpawnParams);
	check(storage != nullptr);

	STORAGE = storage;

	storage->initialize();
}

void AStorage::initialize() {
	TrionixBody = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Models/trionix")));
	check(TrionixBody != nullptr);

	UE_LOG(LogTemp, Warning, TEXT("AStorage initialized"));
}

AStorage& AStorage::GetStorage() {
	/*
	if (STORAGE == nullptr) {
		auto GameMode = UGameplayStatics::GetGameMode(nullptr);
		check(GameMode != nullptr);
		auto World = GameMode->GetWorld();
		check(World != nullptr);

		AStorage::create(World);
		check(STORAGE != nullptr);
	}
	*/

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