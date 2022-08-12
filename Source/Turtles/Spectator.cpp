// Fill out your copyright notice in the Description page of Project Settings.


#include "Spectator.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TurtlePlayerController.h"
//#include "BasicGameModeBase.h"

const float ZOOM_STEP = 100;
const float MIN_ZOOM_DIST = 400;
const float MAX_ZOOM_DIST = 2000;

//UE events and methods

// Sets default values
ASpectator::ASpectator() : Super()
{

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	spring_arm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//RootComponent = Mesh;
	spring_arm->SetupAttachment(RootComponent);
	camera->SetupAttachment(spring_arm, USpringArmComponent::SocketName); //TODO , USpringArmComponent::SocketName ??

	RootComponent->SetWorldLocation(FVector(0.0, 0.0, 200.0));
	//spring_arm->bAbsoluteRotation = true;

	//spring_arm->SetWorldRotation(FRotator(-60.0, -90.0, 0.0)); //Pitch, Yaw, Roll
	auto quat = FRotator(-35.0, 0, 0.0).Quaternion(); //Convert to quaternion
	spring_arm->SetWorldRotation(quat);

	spring_arm->TargetArmLength = 600.0;

	this->OnDestroyed.AddDynamic(this, &ASpectator::Destroyed);
}

// Called when the game starts or when spawned
void ASpectator::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Spec begin play"));
	Super::BeginPlay();

	auto controller = GetController();

	if (controller) {
		auto turtle_controller = Cast<ATurtlePlayerController>(controller);

		if (turtle_controller) {
			turtle_controller->CreateHUD();
		}
	}
}

// Called to bind functionality to input
void ASpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent = PlayerInputComponent;

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ASpectator::zoom_in);//TODO may be and released
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ASpectator::zoom_out);
}

void ASpectator::Reset() {
	Super::Reset();
}

void ASpectator::Restart() {
	Super::Restart();
}

void ASpectator::Destroyed(AActor* DestroyedActor) {
}

void ASpectator::zoom_in() {
	if (spring_arm->TargetArmLength - ZOOM_STEP > MIN_ZOOM_DIST) {
		spring_arm->TargetArmLength -= ZOOM_STEP;
	}else {
		spring_arm->TargetArmLength = MIN_ZOOM_DIST;
	}
}

void ASpectator::zoom_out() {
	if (spring_arm->TargetArmLength + ZOOM_STEP < MAX_ZOOM_DIST) {
		spring_arm->TargetArmLength += ZOOM_STEP;
	}else {
		spring_arm->TargetArmLength = MAX_ZOOM_DIST;
	}
}