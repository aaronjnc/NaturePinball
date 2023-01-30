// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pinball.generated.h"

UCLASS()
class NATUREPINBALL_API APinball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APinball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddForce(FVector Force);

	UFUNCTION()
	void LockBall();

	UFUNCTION()
	void UnlockBall();
	
private:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Ball;	

};
