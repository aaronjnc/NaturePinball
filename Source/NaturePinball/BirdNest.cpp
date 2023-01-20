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
	BoxCollider->OnComponentHit.AddDynamic(this, &ABirdNest::EmptyNest);

	BallSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	BallSpawnPoint->SetupAttachment(Nest);
}

// Called when the game starts or when spawned
void ABirdNest::BeginPlay()
{
	Super::BeginPlay();
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

