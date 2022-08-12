// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Destination.h"
#include "Sound/SoundBase.h"
#include "Turtle.generated.h"

UCLASS()
class TURTLES_API ATurtle : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Pivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* SpawnSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* FinishSound;

	UPROPERTY()
	ADestination* Destination;

public:
	// Sets default values for this pawn's properties
	ATurtle();

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void MoveTurtle(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	int32 GetNumber();

	UFUNCTION(BlueprintCallable)
	void MoveForward(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void MoveBackward(float DeltaTime);

private:
	UWorld& get_world();

	bool CheckDestinationReached();

public:

	void SetDestination(ADestination* NewDestination);
};
