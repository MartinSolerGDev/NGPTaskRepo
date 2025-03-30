// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkateGamemode.generated.h"

/**
 * 
 */
UCLASS()
class NGPTASK_API ASkateGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ASkateGamemode();

protected:

	virtual void BeginPlay() override;

private:

	FTimerHandle GameTimerHandle;
	FTimerHandle DisplayTextTimerHandle;
	int32 PlayerScore;
	int32 MaxScore; 
	float GameTime;

public:
	void IncreaseScore();
	void UpdateTimer();
	void HideQuestText();
};
