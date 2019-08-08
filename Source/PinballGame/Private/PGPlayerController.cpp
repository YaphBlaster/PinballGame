// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "PGFlipper.h"

void APGPlayerController::BeginPlay()
{
	DetectFlippers();
}

void APGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Binding to Actions setup in the Project Settings > Input
	this->InputComponent->BindAction("LeftFlipper", EInputEvent::IE_Pressed, this, &APGPlayerController::LeftFlipperPress);
	this->InputComponent->BindAction("LeftFlipper", EInputEvent::IE_Released, this, &APGPlayerController::LeftFlipperRelease);

	this->InputComponent->BindAction("RightFlipper", EInputEvent::IE_Pressed, this, &APGPlayerController::RightFlipperPress);
	this->InputComponent->BindAction("RightFlipper", EInputEvent::IE_Released, this, &APGPlayerController::RightFlipperRelease);

}

void APGPlayerController::DetectFlippers()
{
	// Array that will store the actors from GetAllActorsOfClass
	TArray<AActor*> ReturnedActors;
	UGameplayStatics::GetAllActorsOfClass(this, APGFlipper::StaticClass(), ReturnedActors);

	// For every Actor in ReturnedActors
	for (AActor* Actor : ReturnedActors)
	{
		// Cast the actor to PGFlipper
		APGFlipper* CastedFlipper = Cast<APGFlipper>(Actor);

		// If the cast was successful
		if (CastedFlipper)
		{
			// We will derive logic based on the Flipper Type
			switch (CastedFlipper->GetFlipperType())
			{
				// In the case of the flipper being a left flipper, ...
				case EFlipperType::FT_Left:
					// Add to the LeftFlipper array
					LeftFlippers.Add(CastedFlipper);
					break;
				// In the case of the flipper being a right flipper, ...
				case EFlipperType::FT_Right:
					// Add to the RightFlipper array
					RightFlippers.Add(CastedFlipper);
					break;
			}
		}
	}

}

void APGPlayerController::RightFlipperPress()
{
	for (APGFlipper* Flipper : RightFlippers)
	{
		Flipper->Flip();
	}
}

void APGPlayerController::RightFlipperRelease()
{
	for (APGFlipper* Flipper : RightFlippers)
	{
		Flipper->Flop();
	}
}

void APGPlayerController::LeftFlipperPress()
{
	for (APGFlipper* Flipper : LeftFlippers)
	{
		Flipper->Flip();
	}
}

void APGPlayerController::LeftFlipperRelease()
{
	for (APGFlipper* Flipper : LeftFlippers)
	{
		Flipper->Flop();
	}
}
