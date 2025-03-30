// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SkateboardCharacter.generated.h"

UCLASS()
class NGPTASK_API ASkateboardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkateboardCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Input functions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void Accelerate();



private:

	//Camera class for the player
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* FirstPersonCameraComponent;

	// Skateboard mesh that will be attach to the player
	UPROPERTY(VisibleAnywhere, Category = "Skateboard")
	class UStaticMeshComponent* SkateMesh;

	//Movement vector for handle the player input movement
	FVector2D CurrentMovementInput;

	float DefaultSpeed;
	float BoostedSpeed;

	bool bCanAccelerate;
	float CooldownTime;

	void StartCooldown();
	void ResetSpeed();
	void EnableAccelerate();

	FTimerHandle CooldownTimerHandle;
	FTimerHandle SpeedIncreaseTimer;

};
