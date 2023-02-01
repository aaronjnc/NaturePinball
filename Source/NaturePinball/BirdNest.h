// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BirdPickup.h"
#include "PaddleManager.h"
#include "Pinball.h"
#include "GameFramework/Actor.h"
#include "BirdNest.generated.h"

class UBoxComponent;

UCLASS()
class NATUREPINBALL_API ABirdNest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABirdNest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddBall();

	UFUNCTION()
	void EmptyNest(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnBall();
	
	void SetBird(ABirdPickup* BirdPickup);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult);

	UFUNCTION()
	void RespawnBall();
	
	FVector GetBirdPosition();

private:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Nest;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BirdCollider;

	UPROPERTY()
	FVector BallSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* BirdPosition;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Pinball;

	UPROPERTY()
	int LockedBalls = 0;

	UPROPERTY(EditAnywhere, Category = "Pinball")
	TSubclassOf<APinball> PinballSubclass;

	UPROPERTY(EditAnywhere, Category = "Pinball")
	APaddleManager* Manager;

	UPROPERTY()
	ABirdPickup* Bird;

	UPROPERTY()
	FTimerHandle SpawnBallTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Pinball")
	float SpawnPauseTime;
};
