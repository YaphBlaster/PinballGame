// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PGFlipper.h"
#include "PGPlayerController.generated.h"

class APGFlipper;
class APGPlunger;

/**
 * 
 */
UCLASS()
class PINBALLGAME_API APGPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<APGFlipper*> LeftFlippers;

	UPROPERTY()
	TArray<APGFlipper*> RightFlippers;

	UPROPERTY()
	APGPlunger* Plunger;

	void DetectFlippers();

	void DetectPlunger();

	void LeftFlipperPress();
	void LeftFlipperRelease();

	void RightFlipperPress();
	void RightFlipperRelease();

	void PlungerPress();
	void PlungerRelease();


public: 
	// Needed to setup the input bindings
	virtual void SetupInputComponent() override;

	APGPlunger* GetPlunger();
	
};
