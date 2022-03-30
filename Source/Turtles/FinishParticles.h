// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "FinishParticles.generated.h"

const float LIFETIME = 1;

UCLASS()
class TURTLES_API AFinishParticles : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* Particles;

private:
	float Lifetime;

public:	
	// Sets default values for this actor's properties
	AFinishParticles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
