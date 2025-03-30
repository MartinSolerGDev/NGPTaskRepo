// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SkateGamemode.h"
#include "Character/SkateboardCharacter.h"
#include "Character/SkatePlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "Character/Widgets/GameplayWidget.h"


ASkateGamemode::ASkateGamemode()
{
	DefaultPawnClass = ASkateboardCharacter::StaticClass();
	PlayerControllerClass = ASkatePlayerController::StaticClass();

	PlayerScore = 0;
	MaxScore = 6;
	GameTime = 180.0f;
}

void ASkateGamemode::BeginPlay()
{
	Super::BeginPlay();

	// Iniciar temporizador de juego
	if (ASkatePlayerController* PlayerController = Cast<ASkatePlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		if (UGameplayWidget* HUD = PlayerController->GetGameplayWidget())
		{
			HUD->ShowQuestText();
		}
	}
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ASkateGamemode::UpdateTimer, 1.0f, true);

	GetWorldTimerManager().SetTimer(DisplayTextTimerHandle, this, &ASkateGamemode::HideQuestText, 1.5f, false);
}

void ASkateGamemode::IncreaseScore()
{
	PlayerScore++;

	if (ASkatePlayerController* PlayerController = Cast<ASkatePlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		if (UGameplayWidget* HUD = PlayerController->GetGameplayWidget())
		{
			HUD->UpdateScore(PlayerScore);
			if (PlayerScore >= MaxScore)
			{
				GetWorldTimerManager().ClearTimer(GameTimerHandle);
				HUD->ShowResultText(true);
			}
		}
	}


}

void ASkateGamemode::UpdateTimer()
{
	GameTime--;
	if (ASkatePlayerController* PlayerController = Cast<ASkatePlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		if (UGameplayWidget* HUD = PlayerController->GetGameplayWidget())
		{
			HUD->UpdateTimerDisplay(GameTime);
			if (GameTime <= 0)
			{
				GetWorldTimerManager().ClearTimer(GameTimerHandle);
				HUD->ShowResultText(false);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("HUD Widget is nullptr!"));
		}
	}
}

void ASkateGamemode::HideQuestText()
{
	if (ASkatePlayerController* PlayerController = Cast<ASkatePlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		if (UGameplayWidget* HUD = PlayerController->GetGameplayWidget())
		{
			HUD->HideQuestText();
		}
	}
}


