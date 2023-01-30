// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pinball.h"
#include "GameFramework/Pawn.h"
#include "Launcher.generated.h"

//class UFloatingPawnMovement;
UCLASS()
class NATUREPINBALL_API ALauncher : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddLauncherPosition(float offset);

	void ReleaseLauncher();

	void SpawnBall();

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* BallLauncher;

	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* BallSpawnPoint;

	UPROPERTY()
		float MaxDistance = 300;

	UPROPERTY()
		FVector OriginPos;

	UPROPERTY()
		FVector MaxPos;

	UPROPERTY()
		float LauncherSpeed = 0;

	UPROPERTY(EditAnywhere, Category = "Pinball")
	TSubclassOf<APinball> PinballSubclass;
};
