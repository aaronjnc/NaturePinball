// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPickup.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MultiballLock.h"
#include "BirdNest.h"
#include "Pinball.h"

// Sets default values
ABirdPickup::ABirdPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BirdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bird Mesh"));
	RootComponent = BirdMesh;

	BallLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Ball Location"));
	BallLocation->SetupAttachment(BirdMesh);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
}

// Called when the game starts or when spawned
void ABirdPickup::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	BallLock->SetBird(this);
	Nest->SetBird(this);
	
}

// Called every frame
void ABirdPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsMoving)
	{
		MovementComponent->ConsumeInputVector();
		MovementComponent->AddInputVector(Dir);
	}
}

void ABirdPickup::SummonBird(FVector SummonPos)
{
	MovementComponent->ConsumeInputVector();
	MovementComponent->Velocity = FVector::Zero();
	Dir = SummonPos - GetActorLocation();
	Dir.Normalize();
	MovementComponent->AddInputVector(Dir);
	bIsMoving = true;
}

void ABirdPickup::GiveBall(APinball* Pinball)
{
	Ball = Pinball;
	Ball->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Ball->SetActorLocation(BallLocation->GetComponentLocation());
	SummonBird(Nest->GetActorLocation());
}

APinball* ABirdPickup::TakeBall()
{
	SummonBird(StartLocation);
	return Ball;
}

