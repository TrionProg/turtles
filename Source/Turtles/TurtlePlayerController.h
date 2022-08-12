// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Spectator.h"
#include "TurtlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TURTLES_API ATurtlePlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	UUserWidget* CurrentWidget;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> TurtleWidgetClass;

	virtual void SetupInputComponent() override;
	
public:
	ATurtlePlayerController();

	void CreateHUD();

private:
	void OnLMBRelase();
	void on_quit_press();//In my engine I am using camel case because it is more readable, I can differ UE4 and my methods and I have no conflicts with Variables/Methods/Blueprint Nodes from UE

	ASpectator& GetSpectator();
	UWorld& get_world();

	void SpawnTurtle();
};
