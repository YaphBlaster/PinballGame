// Fill out your copyright notice in the Description page of Project Settings.


#include "PGFlipper.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>
#include <Kismet/KismetSystemLibrary.h>

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)


// Sets default values
APGFlipper::APGFlipper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	// Initialize Scale vector to (1.0f, 1.0f, 1.0f)
	Scale = FVector::OneVector;

	// Initialize StartRotation and EndRotation Rotators to (0.0f, 0.0f, 0.0f)
	StartRotation = FRotator::ZeroRotator;
	EndRotation = FRotator::ZeroRotator;

	MeshComp->SetupAttachment(SceneComp);
	RootComponent = SceneComp;

	// This is needed for the MoveComponentTo function
	LatentActionInfo.CallbackTarget = this;
	FlipTime = 0.2f;
}

// Called when the game starts or when spawned
void APGFlipper::BeginPlay()
{
	Super::BeginPlay();
}

void APGFlipper::SetDefaults()
{
	switch (FlipperType)
	{
	case EFlipperType::FT_Right:
		StartRotation.Yaw = -20.0f;
		EndRotation.Yaw = 20.0f;
		Scale.X = -1.0f;
		break;
	default:
		StartRotation.Yaw = 20.0f;
		EndRotation.Yaw = -20.0f;
		Scale.X = 1.0f;
		break;
	}

	MeshComp->SetRelativeScale3D(Scale);
	MeshComp->SetRelativeRotation(StartRotation);
}

void APGFlipper::Flip()
{
	UKismetSystemLibrary::MoveComponentTo(MeshComp, FVector::ZeroVector, EndRotation, false, false, FlipTime, false, EMoveComponentAction::Move, LatentActionInfo);
}

void APGFlipper::Flop()
{
	UKismetSystemLibrary::MoveComponentTo(MeshComp, FVector::ZeroVector, StartRotation, false, false, FlipTime, false, EMoveComponentAction::Move, LatentActionInfo);
}

// Called every frame
void APGFlipper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

EFlipperType APGFlipper::GetFlipperType()
{
	return FlipperType;
}

