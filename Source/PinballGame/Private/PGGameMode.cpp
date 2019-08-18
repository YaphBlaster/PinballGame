// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PGPlunger.h"

// Sets default values
APGGameMode::APGGameMode()
{
	Multiplier = 1.0f;
	BallsRemaining = 3;
	HighScoreSaveName = FString(TEXT("HighScore"));
}

void APGGameMode::BeginPlay()
{
	SpawnBall();
	CreateUI();
}

void APGGameMode::SpawnBall()
{
	// Empty array of actors that will be returned
	TArray<AActor*> ReturnedActors;

	// Get all actors that have the Plunger class in our current world and store them in the ReturnedActors array
	UGameplayStatics::GetAllActorsOfClass(this, APGPlunger::StaticClass(), ReturnedActors);

	// As we only have one plunger in the world, we can grab the first element from ReturnedActors and cast it to APGPlunger
	APGPlunger* Plunger = Cast<APGPlunger>(ReturnedActors[0]);

	// If the Plunger exists,
	if (Plunger)
	{
		// Spawn the Ball in the Plunger's BallSpawnLocation
		APGBall* SpawnedBall = GetWorld()->SpawnActor<APGBall>(BallClass, Plunger->GetBallSpawnLocation(), FRotator::ZeroRotator);

		// Hook into the OnDestroyed event and add our OnBallDestroy function to the call
		SpawnedBall->OnDestroyed.AddDynamic(this, &APGGameMode::OnBallDestroy);
	}
}

void APGGameMode::EndGame()
{

}

float APGGameMode::AddSCore(float PointsToAdd)
{
	Score += (PointsToAdd * Multiplier);

	return Score;
}

float APGGameMode::GetScore()
{
	return Score;
}

// Method that will be hooked into the Pinball's OnDestroy method
void APGGameMode::OnBallDestroy(AActor* DestroyedActor)
{
	if (BallsRemaining > 0)
	{
		SpawnBall();
	}
	else 
	{

	}
}

UPGHighScoreSave* APGGameMode::GetSaveGameData()
{
	// NOTE: Checks sometimes need references (asterisk *)
	if (CurrentSaveObject)
	{
		return CurrentSaveObject;
	}
	else
	{
		// Boolean that contains if a save game exists or not
		bool DoesSaveGameExist = UGameplayStatics::DoesSaveGameExist(HighScoreSaveName, 0);

		// If a save game does exist
		if (DoesSaveGameExist)
		{
			// Create a UPGHightScoreSave pointer object;
			UPGHighScoreSave* TempSave = Cast<UPGHighScoreSave>(UGameplayStatics::LoadGameFromSlot(HighScoreSaveName, 0));

			// Sort the save data
			TempSave->SortSaveData();

			// Set the current save object to the temp
			CurrentSaveObject = TempSave;
		}
		// Else a save game does not exist
		else
		{
			// Create a new save game object
			CurrentSaveObject = Cast<UPGHighScoreSave>(UGameplayStatics::CreateSaveGameObject(UPGHighScoreSave::StaticClass()));
		}

		return CurrentSaveObject;

	}
}
