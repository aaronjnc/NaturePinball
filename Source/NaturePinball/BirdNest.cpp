// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdNest.h"
#include "Components/BoxComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ABirdNest::ABirdNest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Nest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nest Mesh"));
	RootComponent = Nest;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(Nest);

	BirdCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bird Collider"));
	BirdCollider->SetupAttachment(Nest);

	BirdPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Bird Position"));
	BirdPosition->SetupAttachment(Nest);

	Pinball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pinball"));
	Pinball->SetupAttachment(Nest);

}

// Called when the game starts or when spawned
void ABirdNest::BeginPlay()
{
	Super::BeginPlay();
	BirdCollider->OnComponentBeginOverlap.AddDynamic(this, &ABirdNest::BeginOverlap);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABirdNest::EmptyNest);
	Pinball->SetVisibility(false);
}

// Called every frame
void ABirdNest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABirdNest::AddBall()
{
	LockedBalls += 1;
}

void ABirdNest::EmptyNest(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA<APinball>() || LockedBalls == 0)
	{
		return;
	}
	//BallSpawnPoint = OtherActor->GetActorLocation();
	BallSpawnPoint = FVector(-310.0, -1454.20459, 265);
	GetWorld()->GetTimerManager().SetTimer(SpawnBallTimerHandle, this, &ABirdNest::SpawnBall, SpawnPauseTime, false);
	UGameplayStatics::PlaySound2D(GetWorld(), BallReleaseSound, 5);
}

void ABirdNest::SpawnBall()
{
	APinball* SpawnedBall = GetWorld()->SpawnActor<APinball>(PinballSubclass, BallSpawnPoint, FRotator::ZeroRotator);
	IncreaseMultiball();
	LockedBalls--;
	if (LockedBalls == 0)
	{
		Pinball->SetVisibility(false);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnBallTimerHandle, this, &ABirdNest::SpawnBall, SpawnPauseTime, false);
	}
}

void ABirdNest::SetBird(ABirdPickup* BirdPickup)
{
	Bird = BirdPickup;
}

void ABirdNest::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABirdPickup>())
	{
		if (!Bird->HasBall())
		{
			return;
		}
		APinball* Ball = Bird->TakeBall();
		Pinball->SetVisibility(true);
		Ball->K2_DestroyActor();
		LockedBalls++;
		RespawnBall();
		UGameplayStatics::PlaySound2D(GetWorld(), BallDropSound, 5);
	}
}

void ABirdNest::RespawnBall_Implementation()
{
}

void ABirdNest::IncreaseMultiball_Implementation()
{
}

FVector ABirdNest::GetBirdPosition()
{
	return BirdPosition->GetComponentLocation();
}

