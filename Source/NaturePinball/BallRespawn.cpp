// Fill out your copyright notice in the Description page of Project Settings.


#include "BallRespawn.h"
#include "Pinball.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ABallRespawn::ABallRespawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap"));
	Box->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABallRespawn::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ABallRespawn::BeginOverlap);
}

void ABallRespawn::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APinball>()) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Paddles active"));

		OtherActor->Destroy();
		Manager->SetLauncherActive();
		Manager->SpawnBall();
		LauncherCheck->DisableWall();
		UGameplayStatics::PlaySound2D(GetWorld(), BallRespawnSound, 1);
	}
}

// Called every frame
void ABallRespawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}