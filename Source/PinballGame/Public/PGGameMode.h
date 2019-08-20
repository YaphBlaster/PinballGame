// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGBall.h"
#include "PGHighScoreSave.h"
#include "PGGameMode.generated.h"

class UPGHighScoreSave;

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

	UPROPERTY()
		float Score;

	UPROPERTY()
		float Multiplier;

	UPROPERTY()
	int32 BallsRemaining;

	void SpawnBall();

	void EndGame();

	// In order to Hook into the OnDestroy Delegate with AddDynamic, we need to have a matching method with a similar signature as the method that will be overridden
	// OnDestroy(AActor* DestroyedActor)
	// UFUNCTION() is also needed to hook into Unreal functions
	UFUNCTION()
		void OnBallDestroy(AActor* DestroyedActor);

	UFUNCTION(BlueprintPure, Category = "Custom Functions")
	UPGHighScoreSave* GetSaveGameData();

	UPROPERTY(VisibleAnywhere, Category = "Variables")
	UPGHighScoreSave* CurrentSaveObject;

	UPROPERTY(BlueprintReadOnly, Category = "Custom Variables")
	FString HighScoreSaveName;

public:
	float AddSCore(float PointsToAdd);

	UFUNCTION(BlueprintPure , Category = "Custom Functions")
		float GetScore();

	// Function is defined in GM_GameMode Blueprint
	// If it is difficult to code a function (Adding UI Widgets to the viewport)
	// Make a function BlueprintImplementable, define it within Blueprints but execute it through code
	UFUNCTION(BlueprintImplementableEvent, Category = "Custom Functions")
		void CreateUI();

	// Function is defined in GM_GameMode Blueprint
	// If it is difficult to code a function (Adding UI Widgets to the viewport)
	// Make a function BlueprintImplementable, define it within Blueprints but execute it through code
	UFUNCTION(BlueprintImplementableEvent, Category = "Custom Functions")
		void CreateHighScoresList();

	// Function is defined in GM_GameMode Blueprint
	// If it is difficult to code a function (Adding UI Widgets to the viewport)
	// Make a function BlueprintImplementable, define it within Blueprints but execute it through code
	UFUNCTION(BlueprintImplementableEvent, Category = "Custom Functions")
		void CreateMainMenu();

	FString GetHighScoreSaveName();
};
