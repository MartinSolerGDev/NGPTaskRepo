// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkatePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NGPTASK_API ASkatePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	ASkatePlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;


private:

	UPROPERTY()
	class UInputMappingContext* InputMapping;

	UPROPERTY()
	class UInputAction* MoveAction;

	UPROPERTY()
	class UInputAction* LookAction;

	UPROPERTY()
	class UInputAction* JumpAction;

	UPROPERTY()
	class UInputAction* AccelerateAction;

	void InitializeInput();

public:

	UInputAction* GetAccelerateAction() const { return AccelerateAction;  }
	UInputAction* GetJumpAction() const { return JumpAction; }
	UInputAction* GetLookAction() const { return LookAction; }
	UInputAction* GetMoveAction() const { UE_LOG(LogTemp, Warning, TEXT("GetMoveAction called. MoveAction: %p"), MoveAction); return MoveAction; }

};
