// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdStart.h"

#include "BirdPickup.h"

// Sets default values
ABirdStart::ABirdStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	BirdCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bird Collider"));
	BirdCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABirdStart::BeginPlay()
{
	Super::BeginPlay();
	BirdCollider->OnComponentBeginOverlap.AddDynamic(this, &ABirdStart::BeginOverlap);
}

// Called every frame
void ABirdStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABirdStart::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ABirdPickup>())
	{
		ABirdPickup* Bird = Cast<ABirdPickup>(OtherActor);
		if (Bird->IsFetchingBall())
		{
			return;
		}
		Bird->StopBird(GetActorLocation(), GetActorRotation());
	}
}

