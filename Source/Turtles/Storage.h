// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Storage.generated.h"

extern AStorage* STORAGE;

//Storage which stores models and assets and may unload them

UCLASS()
class TURTLES_API AStorage : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UStaticMesh* TrionixBody;

public:
	static void create(UWorld* world);

private:
	void initialize();

public:
	static AStorage& GetStorage(UWorld* world);

	AStorage();
	~AStorage();

};
