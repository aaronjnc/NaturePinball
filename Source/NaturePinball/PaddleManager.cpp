// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleManager.h"

// Sets default values
APaddleManager::APaddleManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APaddleManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaddleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LeftPaddleSpeed != 0)
	{
		FRotator NewRotation = FRotator(0, 0, LeftPaddleSpeed * DeltaTime);

		FQuat QuatRotation = FQuat(NewRotation);

		LeftPaddle->AddWorldRotation(QuatRotation, false, 0, ETeleportType::None);
	}

	if (RightPaddleSpeed != 0)
	{
		FRotator NewRotation = FRotator(0, 0, RightPaddleSpeed * DeltaTime);

		FQuat QuatRotation = FQuat(NewRotation);

		RightPaddle->AddWorldRotation(QuatRotation, false, 0, ETeleportType::None);
	}
}

// Called to bind functionality to input
void APaddleManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("LeftPaddle", IE_Pressed, this, &APaddleManager::FlickLeft);
	InputComponent->BindAction("RightPaddle", IE_Pressed, this, &APaddleManager::FlickRight);
}

void APaddleManager::FlickLeft()
{
	LeftPaddleSpeed = 600;
}

void APaddleManager::FlickRight()
{
	RightPaddleSpeed = 600;
}

