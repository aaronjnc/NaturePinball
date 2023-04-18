// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MultiballLock.generated.h"

class ABirdPickup;
class APinball;
UCLASS()
class NATUREPINBALL_API AMultiballLock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiballLock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult);
	
	void SetBird(ABirdPickup* BirdPickup);

	UFUNCTION(BlueprintNativeEvent)
	void AddScore();

	FVector GetBirdPosition();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int Score;

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* LockMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* LockBox;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* BirdPosition;

	UPROPERTY()
	ABirdPickup* Bird;

	UPROPERTY()
	APinball* Ball;
	
};
