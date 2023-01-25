// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleManager.h"

// Sets default values
APaddleManager::APaddleManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;


	// left paddle components
	LPaddlePivot = CreateDefaultSubobject<USceneComponent>(TEXT("Left Paddle Pivot"));
	LPaddlePivot->SetupAttachment(SceneRoot);

	LeftPaddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Paddle"));
	LeftPaddle->SetupAttachment(LPaddlePivot);

	LPaddleBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Paddle Box"));
	LPaddleBox->SetupAttachment(LeftPaddle);

	// right paddle components
	RPaddlePivot = CreateDefaultSubobject<USceneComponent>(TEXT("Right Paddle Pivot"));
	RPaddlePivot->SetupAttachment(SceneRoot);

	RightPaddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Paddle"));
	RightPaddle->SetupAttachment(RPaddlePivot);

	RPaddleBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Paddle Box"));
	RPaddleBox->SetupAttachment(RightPaddle);
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

		LPaddlePivot->AddWorldRotation(QuatRotation, false, 0, ETeleportType::None);

		if (LPaddlePivot->GetComponentRotation().Roll <= -45) {
			LeftPaddleSpeed = 600;
		}

		if (LPaddlePivot->GetComponentRotation().Roll >= 20) {
			LeftPaddleSpeed = 0;
			LPaddlePivot->SetWorldRotation(FRotator(0, 0, 20));
		}
	}

	if (RightPaddleSpeed != 0)
	{
		FRotator NewRotation = FRotator(0, 0, RightPaddleSpeed * DeltaTime);

		FQuat QuatRotation = FQuat(NewRotation);

		RPaddlePivot->AddWorldRotation(QuatRotation, false, 0, ETeleportType::None);

		if (RPaddlePivot->GetComponentRotation().Roll >= 45) {
			RightPaddleSpeed = -600;
		}

		if (RPaddlePivot->GetComponentRotation().Roll <= -20) {
			RightPaddleSpeed = 0;
			RPaddlePivot->SetWorldRotation(FRotator(0, 0, -20));
		}
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
	if (LeftPaddleSpeed == 0)
		LeftPaddleSpeed = -600;
}

void APaddleManager::FlickRight()
{
	if (RightPaddleSpeed == 0)
		RightPaddleSpeed = 600;
}

