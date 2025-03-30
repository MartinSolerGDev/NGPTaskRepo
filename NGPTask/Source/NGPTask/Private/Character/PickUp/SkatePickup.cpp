// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PickUp/SkatePickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Core/SkateGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASkatePickup::ASkatePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
	PickupMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Character/CharacterMeshes/Skate/FinalSkate.FinalSkate")));
	PickupMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	PickupMesh->SetRelativeRotation(FRotator(0.0f, 60.0f, 0.0f));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(150.0f, 100.0f, 50.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASkatePickup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ASkatePickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkatePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float RotationSpeed = 30.0f; // Rotate 90 degrees per second

	// Calculate rotation increment
	FRotator RotationIncrement = FRotator(0.0f, 0.0f, RotationSpeed * DeltaTime);

	// Apply rotation
	AddActorLocalRotation(RotationIncrement);
}

void ASkatePickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (ASkateGamemode* SkateGameMode = Cast<ASkateGamemode>(UGameplayStatics::GetGameMode(GetWorld()))) 
		{
			SkateGameMode->IncreaseScore();

			Destroy();
		}
	}
}

