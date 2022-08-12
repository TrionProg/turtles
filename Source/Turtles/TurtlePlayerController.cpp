// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtlePlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Cave.h"
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

ATurtlePlayerController::ATurtlePlayerController() : Super() {
	bShowMouseCursor = true;

	CurrentWidget = nullptr;
}

void ATurtlePlayerController::CreateHUD()
{
	if (IsLocalController() && TurtleWidgetClass) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), TurtleWidgetClass, TEXT("HUD"));
		if (CurrentWidget != nullptr){
			CurrentWidget->AddToViewport();
		}
	}
}


void ATurtlePlayerController::SetupInputComponent() {
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseLeftButton", IE_Released, this, &ATurtlePlayerController::OnLMBRelase);
	InputComponent->BindAction("Quit", IE_Released, this, &ATurtlePlayerController::on_quit_press).bExecuteWhenPaused = true;
	InputComponent->BindAction("Esc", IE_Released, this, &ATurtlePlayerController::on_quit_press).bExecuteWhenPaused = true;

}

void ATurtlePlayerController::OnLMBRelase() {
	SpawnTurtle();
}

void ATurtlePlayerController::on_quit_press() {
	UKismetSystemLibrary::QuitGame(&get_world(), this, EQuitPreference::Type::Quit, true); 
}

ASpectator& ATurtlePlayerController::GetSpectator() {
	auto pawn = GetPawn();
	auto spectator = (ASpectator*)pawn; //conflict with field of APlayerController

	check(spectator != nullptr);

	return *spectator;
}

UWorld& ATurtlePlayerController::get_world() {
	auto world = GetWorld();
	check(world != nullptr);
	return *world;
}

void ATurtlePlayerController::SpawnTurtle() {
	FHitResult TraceHitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult)) {
		FVector cursor_position = TraceHitResult.Location;

		TArray<AActor*> found_actors;

		UGameplayStatics::GetAllActorsOfClass(&get_world(), ACave::StaticClass(), found_actors);

		for (AActor* abstract_actor : found_actors) {
			ACave* Cave = Cast<ACave>(abstract_actor);

			if (Cave != nullptr) {
				auto Location = Cave->GetActorLocation();
				auto Dist = FVector::Dist2D(cursor_position, Location);

				if (Dist < CAVE_SELECTION_RADIUS) {
					Cave->SpawnTurtle();
				}
			}
		}
	}
}