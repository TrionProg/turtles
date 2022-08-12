// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishParticles.h"

// Sets default values
AFinishParticles::AFinishParticles()
{
 	PrimaryActorTick.bCanEverTick = true;

	UParticleSystem* FinishParticles = Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, TEXT("/Game/Particles/FinishParticles")));
	Particles = CreateDefaultSubobject<UParticleSystemComponent>("Particles");
	Particles->SetTemplate(FinishParticles);

	RootComponent = Particles;

	Lifetime = LIFETIME;
}

// Called when the game starts or when spawned
void AFinishParticles::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishParticles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Lifetime -= DeltaTime;

	if (Lifetime < 0.0) {
		Destroy();
	}
}

