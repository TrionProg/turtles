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
	void on_lmb_release();
	void on_quit_press();

	ASpectator& get_spectator();
	UWorld& get_world();

	void spawn_turtle();
};
