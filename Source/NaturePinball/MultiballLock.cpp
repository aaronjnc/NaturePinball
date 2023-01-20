// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiballLock.h"

// Sets default values
AMultiballLock::AMultiballLock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lock Mesh"));
	RootComponent = LockMesh;

	LockBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lock Overlap"));
	LockBox->SetupAttachment(RootComponent);
	
	//LockBox->OnComponentBeginOverlap.AddDynamic(this, &AMultiballLock::BeginOverlap);
}

// Called when the game starts or when spawned
void AMultiballLock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMultiballLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

