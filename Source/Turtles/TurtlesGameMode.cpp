// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtlesGameMode.h"
#include "Storage.h"

void ATurtlesGameMode::BeginPlay() {
	Super::BeginPlay();

	AStorage::create(GetWorld());
}