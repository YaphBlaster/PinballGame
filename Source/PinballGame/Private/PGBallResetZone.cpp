// Fill out your copyright notice in the Description page of Project Settings.


#include "PGBallResetZone.h"
#include "Components/BoxComponent.h"
#include "PGBall.h"

// Sets default values
APGBallResetZone::APGBallResetZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));

	RootComponent = BoxComp;
	
}

// Called when the game starts or when spawned
void APGBallResetZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APGBallResetZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APGBallResetZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Cast the overlapped actor to a PGBall
	auto* OtherBall = Cast<APGBall>(OtherActor);

	// If the casted actor was indeed a PGBall
	if (OtherBall)
	{
		// Destroy the ball
		// This will call the custom OnBallDestroy function that we have bound to the Ball's OnDestroy method using AddDynamic in PGGameMode
		OtherActor->Destroy();
	}
}

