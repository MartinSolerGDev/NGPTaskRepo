// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateboardCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Character/SkatePlayerController.h>
#include "TimerManager.h"



// Sets default values
ASkateboardCharacter::ASkateboardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// First-Person Camera Setup
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh(), TEXT("head")); // Attach to head bone (optional)
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, -22, 70.0f));
	FirstPersonCameraComponent->SetRelativeRotation(FRotator(0, 90, 90));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//CharacterMesh

	if (GetMesh())
	{
		GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Character/CharacterMeshes/Remy.Remy")));
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f)); // Adjust based on character height
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

		static ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> AnimBlueprintClass(TEXT("/Game/Character/Animations/ABP_Skateboarding.ABP_Skateboarding_C"));
		if (AnimBlueprintClass.Succeeded())
		{
			GetMesh()->SetAnimInstanceClass(AnimBlueprintClass.Object);
		}
	}
	// Skateboard Mesh Setup
	SkateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkateMesh"));
	SkateMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Character/CharacterMeshes/Skate/FinalSkate.FinalSkate")));
	SkateMesh->SetupAttachment(GetMesh());
	SkateMesh->SetRelativeLocation(FVector(-20.0f, 0.0f, 55.0f)); //
	SkateMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SkateMesh->SetRelativeScale3D(FVector(1.f, 1.5f, 1.f));


	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//PlayerVariables
	DefaultSpeed = 600.0f;    // Default walking speed
	BoostedSpeed = 900.f;   // Boosted speed
	CooldownTime = 5.0f;      // Cooldown period in seconds
	bCanAccelerate = true;


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
	if (bCanAccelerate)
	{
		// Increase speed temporarily
		GetCharacterMovement()->MaxWalkSpeed = BoostedSpeed;

		// Prevent multiple speed increases
		bCanAccelerate = false;


		GetWorldTimerManager().SetTimer(SpeedIncreaseTimer, this, &ASkateboardCharacter::ResetSpeed, 3.0f, false);
	}

}

float ASkateboardCharacter::GetAccelerationRemainingTime() const
{
	return GetWorldTimerManager().GetTimerRemaining(SpeedIncreaseTimer);
}

void ASkateboardCharacter::StartCooldown()
{
	// Block acceleration for cooldown period
	GetWorldTimerManager().SetTimer( CooldownTimerHandle, this, &ASkateboardCharacter::EnableAccelerate, CooldownTime, false );
}

void ASkateboardCharacter::ResetSpeed()
{
	//First invalidate timer 
	GetWorldTimerManager().ClearTimer(SpeedIncreaseTimer);


	// Revert to default speed
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;

	// Start cooldown period
	StartCooldown();

}

void ASkateboardCharacter::EnableAccelerate()
{
	//First invalidate timer
	GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
	// Allow acceleration again
	bCanAccelerate = true;
}

