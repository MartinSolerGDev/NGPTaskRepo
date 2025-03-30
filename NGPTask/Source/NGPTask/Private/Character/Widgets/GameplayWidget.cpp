// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Widgets/GameplayWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UGameplayWidget::UpdateAccelerationBar(float CurrentTime, float MaxTime)
{
    if (AccelerationBar)
    {
        if (CurrentTime > 0.0f)
        {
            AccelerationBar->SetVisibility(ESlateVisibility::Visible);
            AccelerationBar->SetPercent(CurrentTime / MaxTime);
        }
        else
        {
            AccelerationBar->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UGameplayWidget::UpdateScore(int32 ScoreValue)
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), ScoreValue)));
    }
}

void UGameplayWidget::UpdateTimerDisplay(float TimeRemaining)
{
    if (TimeText)
    {
        TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.2f"), TimeRemaining)));
    }
}

void UGameplayWidget::ShowResultText(bool hasWin)
{
    if (ResultText)
    {
		ResultText->SetVisibility(ESlateVisibility::Visible);
		if (hasWin)
		{
			ResultText->SetText(FText::FromString(TEXT("You Win!")));
		}
		else
		{
			ResultText->SetText(FText::FromString(TEXT("You Lose!")));
		}
    }
}

void UGameplayWidget::ShowQuestText()
{
    if(QuestText)
	{
        QuestText->SetVisibility(ESlateVisibility::Visible);
		QuestText->SetText(FText::FromString(TEXT("Find the skates before the time runs out!")));
	}
}

void UGameplayWidget::HideQuestText()
{
	if (QuestText)
	{
		QuestText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGameplayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Ensure the bar is hidden at start
    if (AccelerationBar)
    {
        AccelerationBar->SetVisibility(ESlateVisibility::Hidden);
    }
    if (QuestText)
    {
        QuestText->SetVisibility(ESlateVisibility::Hidden);
    }
	if (ResultText)
	{
		ResultText->SetVisibility(ESlateVisibility::Hidden);
	}
}