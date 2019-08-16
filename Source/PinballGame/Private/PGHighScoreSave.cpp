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

		if (count == 0)
		{
			LowestScore = ElementScore;
			LowestIndex = count;
		}

		count++;
	}
}
