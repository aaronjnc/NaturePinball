// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiballLock.h"
#include "Pinball.h"
#include "BirdPickup.h"

// Sets default values
AMultiballLock::AMultiballLock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lock Mesh"));
	RootComponent = LockMesh;

	LockBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lock Overlap"));
	LockBox->SetupAttachment(RootComponent);

	BirdPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Bird Position"));
	BirdPosition->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMultiballLock::BeginPlay()
{
	Super::BeginPlay();
		
	LockBox->OnComponentBeginOverlap.AddDynamic(this, &AMultiballLock::BeginOverlap);
}

// Called every frame
void AMultiballLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMultiballLock::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APinball>())
	{
		if (Bird->HasBall())
		{
			return;
		}
		Ball = Cast<APinball>(OtherActor);
		Ball->LockBall();
		Ball->SetActorLocation(LockBox->GetComponentLocation());
		Ball->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		Bird->SummonBird(GetActorLocation());
	}
	else if (OtherActor->IsA<ABirdPickup>())
	{
		if (Bird->HasBall())
		{
			return;
		}
		Bird->GiveBall(Ball);
	}
}

void AMultiballLock::SetBird(ABirdPickup* BirdPickup)
{
	Bird = BirdPickup;
}

FVector AMultiballLock::GetBirdPosition()
{
	return BirdPosition->GetComponentLocation();
}

