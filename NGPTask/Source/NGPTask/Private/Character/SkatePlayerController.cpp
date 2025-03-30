// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkatePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "InputMappingContext.h"
#include "InputAction.h"

ASkatePlayerController::ASkatePlayerController()
{
}

void ASkatePlayerController::BeginPlay()
{
    Super::BeginPlay();

}

void ASkatePlayerController::Tick(float DeltaTime)
{
}

void ASkatePlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    //UE_LOG(LogTemp, Warning, TEXT("PlayerController: OnPossess called, initializing input..."));

    InitializeInput();
}

void ASkatePlayerController::InitializeInput()
{
    // Load Input Mapping Context
    InputMapping = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Character/Input/InputMapContext"));
    if (!InputMapping)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load InputMappingContext at '/Game/Character/Input/InputMapContext'"));
        return;
    }

    // Load Input Actions
    MoveAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Character/Input/IA_Move.IA_Move"));
    LookAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Character/Input/IA_Look.IA_Look"));
    JumpAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Character/Input/IA_Jump.IA_Jump"));
    AccelerateAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Character/Input/IA_Accelerate.IA_Accelerate"));


    // Validate loaded actions
    if (!MoveAction) { UE_LOG(LogTemp, Error, TEXT("MoveAction is nullptr!")); }
    else UE_LOG(LogTemp, Warning, TEXT("MoveAction successfully loaded."));

    if (!LookAction) { UE_LOG(LogTemp, Error, TEXT("LookAction is nullptr!")); }
    else UE_LOG(LogTemp, Warning, TEXT("LookAction successfully loaded."));

    if (!JumpAction) { UE_LOG(LogTemp, Error, TEXT("JumpAction is nullptr!")); }
    else UE_LOG(LogTemp, Warning, TEXT("JumpAction successfully loaded."));

    if (!AccelerateAction) { UE_LOG(LogTemp, Error, TEXT("AccelerateAction is nullptr!")); }
    else UE_LOG(LogTemp, Warning, TEXT("AccelerateAction successfully loaded."));

    // Add Input Mapping Context to the Player's Input Subsystem
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
        if (Subsystem && InputMapping)
        {
            Subsystem->AddMappingContext(InputMapping, 0);
            UE_LOG(LogTemp, Warning, TEXT("Successfully added Input Mapping Context!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to access UEnhancedInputSubsystem"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to access ULocalPlayer"));
    }

}
