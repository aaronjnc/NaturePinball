// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	UActorComponent* comp = GetComponentByClass(UStaticMeshComponent::StaticClass());
	mesh = Cast<UStaticMeshComponent>(comp);
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (!CurrentVelocity.IsZero())
	//{
	//	FVector NewLocation = mesh->GetComponentLocation() + (CurrentVelocity * DeltaTime);
	//	mesh->SetWorldLocation(NewLocation);
	//}

	if (paddleSpeed != 0)
	{
		FRotator NewRotation = FRotator(0, 0, paddleSpeed * DeltaTime);

		FQuat QuatRotation = FQuat(NewRotation);

		mesh->AddWorldRotation(QuatRotation, false, 0, ETeleportType::None);
	}
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("LeftPaddle", IE_Pressed, this, &APaddle::Flick);
}

void APaddle::Flick()
{
	CurrentVelocity.Z = 400;
	paddleSpeed = 600;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}