// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turtle.h"
#include "Destination.h"
#include "Cave.generated.h"

const float SPAWN_INTERVAL = 2.0;
const float CAVE_SELECTION_RADIUS = 200.0;

UCLASS()
class TURTLES_API ACave : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Turtle)
	TSubclassOf<class ATurtle> Turtle;  

	UPROPERTY(EditAnywhere, Category = Destination)
	class ADestination* Destination;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Body;

	float SpawnInterval;
	
public:	
	// Sets default values for this actor's properties
	ACave();

	void SpawnTurtle();

private:
	UWorld& get_world();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
