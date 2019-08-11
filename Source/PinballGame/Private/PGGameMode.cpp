// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameMode.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

APGGameMode::APGGameMode()
{

}

void APGGameMode::BeginPlay()
{
	SpawnBallBP();
}
