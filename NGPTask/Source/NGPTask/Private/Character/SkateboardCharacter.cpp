// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateboardCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Character/SkatePlayerController.h>



// Sets default values
ASkateboardCharacter::ASkateboardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// First-Person Camera Setup
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh(), TEXT("head")); // Attach to head bone (optional)
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 22, 30.0f));
	FirstPersonCameraComponent->SetRelativeRotation(FRotator(0, 90, 90));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//CharacterMesh

	GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Character/CharacterMeshes/Remy.Remy")));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f)); // Adjust based on character height
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));


	// Skateboard Mesh Setup
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		ASkatePlayerController* SkateController = Cast<ASkatePlayerController>(GetController());
		if (SkateController)
		{
			UE_LOG(LogTemp, Warning, TEXT("SkateController obtained successfully in ASkateboardCharacter."));

			if (SkateController->GetMoveAction())
			{
				EnhancedInputComponent->BindAction(SkateController->GetMoveAction(), ETriggerEvent::Triggered, this, &ASkateboardCharacter::Move);
			
			}

			if (SkateController->GetLookAction())
			{
				EnhancedInputComponent->BindAction(SkateController->GetLookAction(), ETriggerEvent::Triggered, this, &ASkateboardCharacter::Look);
				
			}

			if (SkateController->GetJumpAction())
			{
				EnhancedInputComponent->BindAction(SkateController->GetJumpAction(), ETriggerEvent::Triggered, this, &ASkateboardCharacter::Jump);
				
			}

			if (SkateController->GetAccelerateAction())
			{
				EnhancedInputComponent->BindAction(SkateController->GetAccelerateAction(), ETriggerEvent::Triggered, this, &ASkateboardCharacter::Accelerate);
				
			}
		}

	}

}

void ASkateboardCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("Move function called."));
	CurrentMovementInput = MovementVector;
	if (Controller && MovementVector.SizeSquared() > 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		
	}
}

void ASkateboardCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	if (LookVector.SizeSquared() > 0.0f)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void ASkateboardCharacter::Jump()
{
	ACharacter::Jump();
}

void ASkateboardCharacter::Accelerate()
{

}

