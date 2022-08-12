// Fill out your copyright notice in the Description page of Project Settings.


#include "Turtle.h"
#include "Storage.h"
#include "Engine/ObjectLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FinishParticles.h"

const float DESTINATION_DISTANCE = 50;
const float TURTLE_SPEED = 300;

// Sets default values
ATurtle::ATurtle()
{
	PrimaryActorTick.bCanEverTick = true;

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));

	//I can make movement component, collision and move turtle by NavMesh, but I have no time for that and task do not says about it.

	RootComponent = Pivot;
	Body = nullptr; //Body will be loaded in BeginPlay, that is why user can not see body in icon of asset, I've made it for lulz.

	Pivot->SetMobility(EComponentMobility::Type::Movable);
}

// Called when the game starts or when spawned
void ATurtle::BeginPlay()
{
	Super::BeginPlay();

	Body = NewObject <UStaticMeshComponent>(this);

	//Load model, which stored in Storage, Storage has been crated by GameMode::BeginPlay
	//I've tryed two ways to store static mesh, but UObjectLibrary is strange because where are not key->value access to assets
	//Storage is just an Cache, it may anload models if it is needed(in the future)
	AStorage& Storage = AStorage::GetStorage(GetWorld());
	auto Result = Body->SetStaticMesh(Storage.TrionixBody);
	Body->SetupAttachment(Pivot);
	check(Result != false);

	/*
	//Or load model from file
	UStaticMesh* BodyMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Models/trionix")));
	auto Result = Body->SetStaticMesh(BodyMesh);
	Body->SetupAttachment(Pivot);
	check(Result != false);
	*/

	Body->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));

	Body->SetMobility(EComponentMobility::Type::Movable);
	Body->RegisterComponent();

	if (SpawnSound != nullptr) {
		UGameplayStatics::PlaySound2D(this, SpawnSound, 1.0, 1.0, 0.0, nullptr, nullptr, false);
	}
}

// Called every frame
void ATurtle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CheckDestinationReached()) {
		MoveTurtle(DeltaTime);
	}
}


void ATurtle::MoveForward(float DeltaTime){
	auto Location = GetActorLocation();
	auto NewLocation = FVector(
		Location.X,
		Location.Y + TURTLE_SPEED * DeltaTime,
		Location.Z
	);

	SetActorLocation(NewLocation);
}

void ATurtle::MoveBackward(float DeltaTime){
	auto Location = GetActorLocation();
	auto NewLocation = FVector(
		Location.X,
		Location.Y - TURTLE_SPEED * DeltaTime,
		Location.Z
	);

	SetActorLocation(NewLocation);
}

UWorld& ATurtle::get_world() {
	auto World = GetWorld();
	check(World != nullptr);

	return *World;
}

bool ATurtle::CheckDestinationReached() {
	if (Destination != nullptr) {
		auto TurtlePos = GetActorLocation();
		auto DestinationPos = Destination->GetActorLocation();
		auto Distance = FVector::Distance(TurtlePos, DestinationPos);

		if (Distance < DESTINATION_DISTANCE) {
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			get_world().SpawnActor<AFinishParticles>(AFinishParticles::StaticClass(), GetActorLocation(), GetActorRotation(), ActorSpawnParams);

			Destroy();

			if (FinishSound != nullptr) {
				UGameplayStatics::PlaySound2D(this, FinishSound, 1.0, 1.0, 0.0, nullptr, nullptr, false);
			}

			return true;
		}

	}

	return false;
}

void ATurtle::SetDestination(ADestination* NewDestination) {
	Destination = NewDestination;
}