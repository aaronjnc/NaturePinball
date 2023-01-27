// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"

// Sets default values
ALauncher::ALauncher()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallLauncher = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Launcher Mesh"));
	RootComponent = BallLauncher;
}

// Called when the game starts or when spawned
void ALauncher::BeginPlay()
{
	Super::BeginPlay();
	
	// origin is based off initial position
	OriginZ = BallLauncher->GetRelativeLocation().Z;
	MinZ += OriginZ;
}

// Called every frame
void ALauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LauncherSpeed != 0) {
		FVector newLocation = BallLauncher->GetRelativeLocation() + FVector(0, 0, LauncherSpeed * DeltaTime);
		if (newLocation.Z >= OriginZ) {
			newLocation.Z = OriginZ;
			LauncherSpeed = 0;
		}

		BallLauncher->SetRelativeLocation(newLocation);
	}
}

void ALauncher::AddLauncherPosition(FVector offset)
{
	FVector newLocation = BallLauncher->GetRelativeLocation() + offset;

	if (newLocation.Z <= OriginZ && newLocation.Z >= MinZ) {
		BallLauncher->SetRelativeLocation(newLocation);
	}
}

void ALauncher::ReleaseLauncher()
{
	LauncherSpeed = (OriginZ - BallLauncher->GetRelativeLocation().Z) * 10;
}

