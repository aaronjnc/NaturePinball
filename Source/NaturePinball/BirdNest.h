// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void EmptyNest(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Result);

private:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Nest;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* BallSpawnPoint;

	UPROPERTY()
	int LockedBalls = 0;

	UPROPERTY(EditAnywhere, Category = "Pinball")
	TSubclassOf<APinball> PinballSubclass;

};
