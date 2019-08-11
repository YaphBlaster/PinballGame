// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlunger.h"
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Components/SceneComponent.h>
#include "Kismet/KismetMathLibrary.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)


// Sets default values
APGPlunger::APGPlunger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	PlungerTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	MeshComp->SetRelativeScale3D(FVector(6.0f));
	MeshComp->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	RootComponent = DefaultSceneRoot;

	// Setting Vectors
	PlungerStart = FVector::ZeroVector;
	PlungerEnd = FVector(0.0f, 150.0f, 0.0f);
	BallLocation = FVector(0.0f, -300.0f, 0.0f);

	LatentActionInfo.CallbackTarget = this;
}

// Called when the game starts or when spawned
void APGPlunger::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat InterpFunc;

	// Check if curve asset reference is valid
	if (FloatCurve)
	{
		// Bind our Update function to the InterpFunc from FOnTimelineFloat
		InterpFunc.BindUFunction(this, FName("Update"));

		// Add the float curve to the Timeline and connect to the InterpFunction's delegate
		// The float alpha output will have the name of the third parameter
		PlungerTimeline->AddInterpFloat(FloatCurve, InterpFunc, FName("Charge Alpha"));

		// Setting our TimeLine's settings before we start it
		PlungerTimeline->SetLooping(false);
		PlungerTimeline->SetIgnoreTimeDilation(true);
	}
	
}

void APGPlunger::Update(float value)
{
	// Pull the Plunger back by lerping the position of the Plunger by using the Alpha (parameter labelled 'value') that is returned from the Timeline
	MeshComp->SetRelativeLocation(FMath::Lerp(PlungerStart, PlungerEnd, value));
}

FVector APGPlunger::GetBallSpawnLocation()
{
	// https://api.unrealengine.com/INT/API/Runtime/Engine/Kismet/UKismetMathLibrary/TransformLocation/index.html
	// Transform a position by the supplied transform. For example, if T was an object's transform, this would transform a position from local space to world space.
	// TransformLocation will translate LocalSpace to WorldSpace that is needed by the SpawnActor method
	return UKismetMathLibrary::TransformLocation(GetActorTransform(), BallLocation);
}

// Called every frame
void APGPlunger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APGPlunger::ChargePlunger()
{
	// Play TimeLine
	PlungerTimeline->PlayFromStart();
}

void APGPlunger::StopCharge()
{
	PlungerTimeline->Stop();
	UKismetSystemLibrary::MoveComponentTo(MeshComp, FVector::ZeroVector, FRotator::ZeroRotator, false, false, 0.1f, false, EMoveComponentAction::Move, LatentActionInfo);
}

