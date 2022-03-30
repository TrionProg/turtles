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
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));

	RootComponent = Pivot;

	Pivot->SetMobility(EComponentMobility::Type::Movable);
}

// Called when the game starts or when spawned
void ATurtle::BeginPlay()
{
	Super::BeginPlay();

	Body = NewObject <UStaticMeshComponent>(this);

	UStaticMesh* BodyMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Models/trionix")));
	auto Result = Body->SetStaticMesh(BodyMesh);
	Body->SetupAttachment(Pivot);
	check(Result != false);

	//auto Storage = UObjectLibrary::CreateLibrary(UObjectLibrary::StaticClass(), false, GIsEditor);

	/*
	AStorage& Storage = AStorage::GetStorage();
	auto Result = Body->SetStaticMesh(Storage.TrionixBody);
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
/*
void ATurtle::MoveTurtle(float DeltaTime) {
	MoveForward(DeltaTime);
}
*/

void ATurtle::MoveForward(float DeltaTime){
	auto location = GetActorLocation();
	auto new_location = FVector(
		location.X,
		location.Y + TURTLE_SPEED * DeltaTime,
		location.Z
	);

	SetActorLocation(new_location);
}

void ATurtle::MoveBackward(float DeltaTime){
	auto location = GetActorLocation();
	auto new_location = FVector(
		location.X,
		location.Y - TURTLE_SPEED * DeltaTime,
		location.Z
	);

	SetActorLocation(new_location);
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
/*
// Called to bind functionality to input
void ATurtle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/

