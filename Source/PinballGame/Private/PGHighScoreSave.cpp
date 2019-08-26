// Fill out your copyright notice in the Description page of Project Settings.


#include "PGHighScoreSave.h"
#include "Kismet/KismetMathLibrary.h"
#include "PGGameMode.h"
#include "Kismet/GameplayStatics.h"

UPGHighScoreSave::UPGHighScoreSave()
{
}

FHighScoreStruct UPGHighScoreSave::DetermineLowestScoreValue()
{
	float LowestScore = 0.0f;
	int32 LowestIndex = 0;

	int32 count = 0;

	for (FHighScoreStruct SaveItem : SaveItemsStruct)
	{
		float ElementScore = SaveItem.Score;

		// If this is the first element of the array
		if (count == 0)
		{
			// Set the LowestScore to the current ElementScore
			// Set the LowestIndex to the current count (which will be zero)
			LowestScore = ElementScore;
			LowestIndex = count;
		}
		// Else this is every other element
		else {

			// If the current ElementScore is less than the current LowestScore
			if (ElementScore < LowestScore)
			{
				// Set the LowestScore to the current ElementScore
				// Set the LowestIndex to the current count
				LowestScore = ElementScore;
				LowestIndex = count;
			}
			
		}

		// Increment the count
		count++;
	}

	LowestScoreStruct = SaveItemsStruct[LowestIndex];
	LowestScoreIndex = LowestIndex;

	return LowestScoreStruct;
}

FHighScoreStruct UPGHighScoreSave::DetermineHighestScoreValue()
{
	float HighestScore = 0.0f;
	int32 HighestIndex = 0;

	int32 count = 0;

	for (FHighScoreStruct SaveItem : SaveItemsStruct)
	{
		float ElementScore = SaveItem.Score;

		// If this is the first element of the array
		if (count == 0)
		{
			// Set the HighestScore to the current ElementScore
			// Set the HighestIndex to the current count (which will be zero)
			HighestScore = ElementScore;
			HighestIndex = count;
		}
		// Else this is every other element
		else {

			// If the current ElementScore is greater than the current HighestScore
			if (ElementScore > HighestScore)
			{
				// Set the HighestScore to the current ElementScore
				// Set the HighestIndex to the current count
				HighestScore = ElementScore;
				HighestIndex = count;
			}

		}

		// Increment the count
		count++;
	}

	HighestScoreStruct = SaveItemsStruct[HighestIndex];
	HighestScoreIndex = HighestIndex;

	return HighestScoreStruct;
}

void UPGHighScoreSave::SortSaveData()
{
	// Create a temporary high score structs array and set it to the current SaveItemsStruct
	TArray<FHighScoreStruct> TempSaveStructs;

	// While there are elements in the SaveItemsStruct
	while (SaveItemsStruct.Num() > 0)
	{
		// Add the Highest Struct Value to the TempSaveStructs
		TempSaveStructs.Add(DetermineHighestScoreValue());

		// Remove an item from the SaveItemsStruct at the HighestScoreIndex
		SaveItemsStruct.RemoveAt(HighestScoreIndex);
	}

	// Set the SaveItemsStruct to be the TempSaveStructs
	SaveItemsStruct = TempSaveStructs;
}

void UPGHighScoreSave::AddHighScore(FHighScoreStruct NewScore)
{
	SaveItemsStruct.Add(NewScore);
	SortSaveData();
	SaveItemsStruct.SetNum(UKismetMathLibrary::Min(4.0f, SaveItemsStruct.Num()));
}

TArray<FHighScoreStruct> UPGHighScoreSave::GetSaveItemsStruct()
{
	return SaveItemsStruct;
}

