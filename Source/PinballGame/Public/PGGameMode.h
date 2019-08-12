// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGBall.h"
#include "PGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PINBALLGAME_API APGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APGGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Ball")
	TSubclassOf<APGBall> BallClass;

	float Score;
	float Multiplier;

	void SpawnBall();

	// In order to Hook into the OnDestroy Delegate with AddDynamic, we need to have a matching method with a similar signature as the method that will be overridden
	// OnDestroy(AActor* DestroyedActor)
	// UFUNCTION() is also needed to hook into Unreal functions
	UFUNCTION()
		void OnBallDestroy(AActor* DestroyedActor);

public:
	float AddSCore(float PointsToAdd);

};
