// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdPickup.generated.h"

class AMultiballLock;
class UFloatingPawnMovement;
class ABirdNest;
class APinball;
UCLASS()
class NATUREPINBALL_API ABirdPickup : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABirdPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SummonBird(FVector SummonPos);

	void GiveBall(APinball* Pinball);

	APinball* TakeBall();

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* BirdMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* BallLocation;

	UPROPERTY(EditAnywhere, Category = "Componets")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, Category = "Multiball Parts")
	ABirdNest* Nest;

	UPROPERTY(EditAnywhere, Category = "Multiball Parts")
	AMultiballLock* BallLock;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	bool bIsMoving;

	UPROPERTY()
	FVector Dir;

	UPROPERTY()
	FVector StartPos;

	UPROPERTY()
	APinball* Ball;

};
