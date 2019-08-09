// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PINBALLGAME_API APGGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnBall();

public:
	APGGameMode()
};
