// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SkateGamemode.h"
#include "Character/SkateboardCharacter.h"
#include "Character/SkatePlayerController.h"


ASkateGamemode::ASkateGamemode()
{
	DefaultPawnClass = ASkateboardCharacter::StaticClass();
	PlayerControllerClass = ASkatePlayerController::StaticClass();
	UE_LOG(LogTemp, Warning, TEXT("ASkateGamemode constructor called."));
}

void ASkateGamemode::BeginPlay()
{
	Super::BeginPlay();
}


