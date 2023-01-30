// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherCheck.h"
#include "Pinball.h"

// Sets default values
ALauncherCheck::ALauncherCheck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap"));
	Box->SetupAttachment(RootComponent);

	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	Wall->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALauncherCheck::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALauncherCheck::BeginOverlap);
	DisableWall();
}

void ALauncherCheck::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APinball>()) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Paddles active"));

		Manager->SetLauncherInactive();
		Wall->SetHiddenInGame(false);
		Wall->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}
}

// Called every frame
void ALauncherCheck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALauncherCheck::DisableWall()
{
	Wall->SetHiddenInGame(true);
	Wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

