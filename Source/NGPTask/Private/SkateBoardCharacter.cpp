// Fill out your copyright notice in the Description page of Project Settings.


#include "SkateBoardCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
ASkateBoardCharacter::ASkateBoardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Content/Content/Character/Remy.uasset"))); 
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f)); // Adjust based on character height
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


	//Camera Creation and setup
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh(), TEXT("head")); // Attach to head bone (optional)
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 60.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

// Called when the game starts or when spawned
void ASkateBoardCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			//TODO
		}
	}
}

// Called every frame
void ASkateBoardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkateBoardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASkateBoardCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	CurrentMovementInput = MovementVector;
	if (Controller && MovementVector.SizeSquared() > 0.0f)
	{
		// Get forward and right vectors
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		// Add movement input
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASkateBoardCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (LookVector.SizeSquared() > 0.0f)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void ASkateBoardCharacter::JumpAction()
{
	Jump();
}

void ASkateBoardCharacter::Accelerate()
{
}

