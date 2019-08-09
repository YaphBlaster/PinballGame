// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameMode.h"


void APGGameMode::BeginPlay()
{

}

void APGGameMode::SpawnBall()
{
	// Iterate over all the player controllers available
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		// Store the player controller from the iterator
		APGPlayerController* PC = Cast<APGPlayerController>(Iterator->Get());
	}
}
