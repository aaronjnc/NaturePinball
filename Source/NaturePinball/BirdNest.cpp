// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdNest.h"
#include "Components/BoxComponent.h"

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

	BallSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	BallSpawnPoint->SetupAttachment(Nest);

	BirdPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Bird Position"));
	BirdPosition->SetupAttachment(Nest);
}

// Called when the game starts or when spawned
void ABirdNest::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentHit.AddDynamic(this, &ABirdNest::EmptyNest);
	BirdCollider->OnComponentBeginOverlap.AddDynamic(this, &ABirdNest::BeginOverlap);
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

void ABirdNest::EmptyNest(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Result)
{
	FVector SpawnPoint = BallSpawnPoint->GetComponentLocation();
	for (int i = 0; i < LockedBalls; i++)
	{
		APinball* SpawnedBall = GetWorld()->SpawnActor<APinball>(PinballSubclass, SpawnPoint, FRotator::ZeroRotator);
	}
	LockedBalls = 0;
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
		APinball* Pinball = Bird->TakeBall();
		if (LockedBalls == 0)
		{
			Pinball->SetActorLocation(Nest->GetComponentLocation());
			Pinball->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		}
		LockedBalls++;
	}
}

FVector ABirdNest::GetBirdPosition()
{
	return BirdPosition->GetComponentLocation();
}

