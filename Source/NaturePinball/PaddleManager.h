// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "PaddleManager.generated.h"

UCLASS()
class NATUREPINBALL_API APaddleManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void FlickLeft();

	void FlickRight();

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* LPaddlePivot;

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* LeftPaddle;

	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* LPaddleBox;

	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* RPaddlePivot;

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* RightPaddle;

	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* RPaddleBox;

	UPROPERTY()
		float LeftPaddleSpeed = 0;

	UPROPERTY()
		float RightPaddleSpeed = 0;

};