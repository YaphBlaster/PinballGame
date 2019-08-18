// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PGHighScoreSave.generated.h"


USTRUCT()
struct FHighScoreStruct
{
	GENERATED_BODY()

public:
	// Send vector information over the network
	// Less precise but less data to move also
	UPROPERTY()
		FText Name;

	UPROPERTY()
		float Score;

	void SetName(FString NewName)
	{
		Name = FText::FromString(NewName);
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
	UPROPERTY()
	TArray<FHighScoreStruct> SaveItemsStruct;

	UPROPERTY()
	FHighScoreStruct LowestScoreStruct;

	UPROPERTY()
	FHighScoreStruct HighestScoreStruct;
	
	int32 LowestScoreIndex;
	int32 HighestScoreIndex;


public:
	FHighScoreStruct DetermineLowestScoreValue();
	FHighScoreStruct DetermineHighestScoreValue();
	void SortSaveData();

};
