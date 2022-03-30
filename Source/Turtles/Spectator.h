// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Spectator.generated.h"

UCLASS()
class TURTLES_API ASpectator : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* spring_arm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* camera;

//UE events and methods
protected:
	UFUNCTION()
	void Destroyed(AActor* DestroyedActor);

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Reset() override;
	virtual void Restart() override;

public:
	// Sets default values for this pawn's properties
	ASpectator();
//My methods and events
private:
	void zoom_in();
	void zoom_out();
};
