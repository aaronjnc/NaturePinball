// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void AddLauncherPosition(FVector offset);

	void ReleaseLauncher();

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* BallLauncher;

	UPROPERTY()
		float OriginZ = 0;

	UPROPERTY()
		float MinZ = -300;

	UPROPERTY()
		float LauncherSpeed = 0;
};
