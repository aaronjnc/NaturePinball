// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

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

	if (bLauncherActive && bMouseDown) {
		float mouseX;
		float mouseY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);

		Launcher->AddLauncherPosition(FVector(0, 0, PreviousMouseY - mouseY));

		PreviousMouseY = mouseY;
	}

	if (LeftPaddleSpeed != 0)
	{
		FRotator NewRotation = FRotator(0, 0, LeftPaddleSpeed * DeltaTime);

		FQuat QuatRotation = FQuat(NewRotation);

		LPaddlePivot->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);

		if (LPaddlePivot->GetRelativeRotation().Roll <= -45) {
			LeftPaddleSpeed = 600;
		}

		if (LPaddlePivot->GetRelativeRotation().Roll >= 20) {
			LeftPaddleSpeed = 0;
			LPaddlePivot->SetRelativeRotation(FRotator(0, 0, 20));
		}
	}

	if (RightPaddleSpeed != 0)
	{
		FRotator NewRotation = FRotator(0, 0, RightPaddleSpeed * DeltaTime);

		FQuat QuatRotation = FQuat(NewRotation);

		RPaddlePivot->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);

		if (RPaddlePivot->GetRelativeRotation().Roll >= 45) {
			RightPaddleSpeed = -600;
		}

		if (RPaddlePivot->GetRelativeRotation().Roll <= -20) {
			RightPaddleSpeed = 0;
			RPaddlePivot->SetRelativeRotation(FRotator(0, 0, -20));
		}
	}
}

// Called to bind functionality to input
void APaddleManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("LeftPaddle", IE_Pressed, this, &APaddleManager::LeftMouseClicked);
	InputComponent->BindAction("LeftPaddle", IE_Released, this, &APaddleManager::LeftMouseReleased);
	InputComponent->BindAction("RightPaddle", IE_Pressed, this, &APaddleManager::FlickRight);
}

void APaddleManager::LeftMouseClicked()
{
	if (!bLauncherActive)
		FlickLeft();
	else {
		bMouseDown = true;
		float mouseX;
		float mouseY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
		PreviousMouseY = mouseY;
	}
}

void APaddleManager::LeftMouseReleased()
{
	if (bLauncherActive && bMouseDown) {
		bMouseDown = false;
		Launcher->ReleaseLauncher();
	}
}

void APaddleManager::FlickLeft()
{
	if (LeftPaddleSpeed == 0)
		LeftPaddleSpeed = -600;
}

void APaddleManager::FlickRight()
{
	if (!bLauncherActive && RightPaddleSpeed == 0)
		RightPaddleSpeed = 600;
}

void APaddleManager::SetLauncherActive()
{
	bLauncherActive = true;
}

void APaddleManager::SetLauncherInactive()
{
	bLauncherActive = false;
}

