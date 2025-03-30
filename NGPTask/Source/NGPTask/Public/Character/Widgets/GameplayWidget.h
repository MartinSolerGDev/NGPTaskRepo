// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class NGPTASK_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable)
    void UpdateAccelerationBar(float CurrentTime, float MaxTime);

    UFUNCTION(BlueprintCallable)
    void UpdateScore(int32 ScoreValue);

    UFUNCTION(BlueprintCallable)
    void UpdateTimerDisplay(float TimeRemaining);

    UFUNCTION(BlueprintCallable)
    void ShowResultText(bool hasWIn);

    UFUNCTION(BlueprintCallable)
    void ShowQuestText();

    UFUNCTION(BlueprintCallable)
    void HideQuestText();

protected:
    
    virtual void NativeConstruct() override;

private:

    UPROPERTY(meta = (BindWidget))
    UProgressBar* AccelerationBar;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TimeText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ResultText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* QuestText;
};
