// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaddleManager.h"
#include "LauncherCheck.h"
#include <Runtime/Engine/Classes/Components/BoxComponent.h>
#include "BallRespawn.generated.h"

UCLASS()
class NATUREPINBALL_API ABallRespawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallRespawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* Box;

	UPROPERTY(EditAnywhere, Category = "Manager")
		APaddleManager* Manager;

	UPROPERTY(EditAnywhere, Category = "Manager")
		ALauncherCheck* LauncherCheck;
};
