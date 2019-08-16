// Fill out your copyright notice in the Description page of Project Settings.


#include "PGHighScoreSave.h"

UPGHighScoreSave::UPGHighScoreSave()
{

}

void UPGHighScoreSave::DetermineLowestScoreValue()
{
	float LowestScore;
	int32 LowestIndex;

	int32 count = 0;

	for (FHighScoreStruct SaveItem : SaveStruct)
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
}

