// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateboardCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
ASkateboardCharacter::ASkateboardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ? First-Person Camera Setup
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh(), TEXT("head")); // Attach to head bone (optional)
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 60.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ASkateboardCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkateboardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkateboardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASkateboardCharacter::Move(const FInputActionValue& Value)
{
}

void ASkateboardCharacter::Look(const FInputActionValue& Value)
{
}

void ASkateboardCharacter::JumpAction()
{
}

void ASkateboardCharacter::Accelerate(bool bAccelerate)
{

}

