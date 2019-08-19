// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PGHighScoreSave.generated.h"

// In order to reference the structs in blueprints, (BlueprintType) has to passed into the USTRUCT constructor
USTRUCT(BlueprintType)
struct FHighScoreStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Custom Variables")
		FText Name;

	UPROPERTY(BlueprintReadWrite, Category = "Custom Variables")
		float Score;

	float GetScore()
	{
		return Score;
	}

	FHighScoreStruct()
	{
		Name = FText::FromString("Default");
		Score = 0.0f;
	}

};


/**
 * 
 */
UCLASS()
class PINBALLGAME_API UPGHighScoreSave : public USaveGame
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UPGHighScoreSave();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Variables")
	TArray<FHighScoreStruct> SaveItemsStruct;

	UPROPERTY()
	FHighScoreStruct LowestScoreStruct;

	UPROPERTY()
	FHighScoreStruct HighestScoreStruct;
	
	UPROPERTY()
	int32 LowestScoreIndex;

	UPROPERTY()
	int32 HighestScoreIndex;


public:
	FHighScoreStruct DetermineLowestScoreValue();
	FHighScoreStruct DetermineHighestScoreValue();
	void SortSaveData();

	UFUNCTION(BlueprintCallable, Category = "Custom Functions")
	void AddHighScore(FHighScoreStruct NewScore);

	UFUNCTION(BlueprintPure, Category = "Custom Functions")
	TArray<FHighScoreStruct> GetSaveItemsStruct();
};
