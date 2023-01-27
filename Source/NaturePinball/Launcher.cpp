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
	OriginPos = BallLauncher->GetRelativeLocation();
	MaxPos = OriginPos + MaxDistance * -GetActorUpVector();
}

// Called every frame
void ALauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LauncherSpeed != 0) {
		FVector newLocation = BallLauncher->GetRelativeLocation() + GetActorUpVector() * LauncherSpeed * DeltaTime;

		FVector dist = newLocation - OriginPos;
		float dot = dist.Dot(GetActorUpVector());

		if (dot >= 0) {
			newLocation = OriginPos;
			LauncherSpeed = 0;
		}

		BallLauncher->SetRelativeLocation(newLocation);
	}
}

void ALauncher::AddLauncherPosition(float offset)
{
	FVector newLocation = BallLauncher->GetRelativeLocation() + GetActorUpVector() * offset;

	if (MaxPos.Z > OriginPos.Z && newLocation.Z <= MaxPos.Z && newLocation.Z >= OriginPos.Z
		|| MaxPos.Z < OriginPos.Z && newLocation.Z >= MaxPos.Z && newLocation.Z <= OriginPos.Z) {
		BallLauncher->SetRelativeLocation(newLocation);
	}
}

void ALauncher::ReleaseLauncher()
{
	LauncherSpeed = FVector::Distance(OriginPos, BallLauncher->GetRelativeLocation()) * 10;
}

