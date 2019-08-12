// Fill out your copyright notice in the Description page of Project Settings.


#include "PGBall.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
APGBall::APGBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);

	// Needed for collision detection
	MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	
	RootComponent = MeshComp;

	DefaultSpeed = FVector(0.0f, -2000.0f, 0.0f);
	TableStickyness = 5000.0f;

}

// Called when the game starts or when spawned
void APGBall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APGBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Make the static mesh (ball) move to the bottom of the screen with an impulse
	MeshComp->AddImpulse(DefaultSpeed * DeltaTime, NAME_None, true);

	// Where we will store the result of our LineTrace (will be used later)
	FHitResult OutHit;

	// Starting and ending location vectors of the LineTrace
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.0f, 0.0f, 500.0f);
		
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 2);

	// Store hit result in OutHit
	// OutHit will have access to all regular HitResult properties within it (in blueprints we have to select the OutHit pin and then break it)
	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);

	if (isHit)
	{
		// Impact normal is the direction of the LineTrace
		FVector StickyVector = (OutHit.ImpactNormal * TableStickyness * DeltaTime) * -1;

		// Add impulse in the direction of the hit object
		MeshComp->AddImpulse(StickyVector, NAME_None, true);
	}
}

UStaticMeshComponent* APGBall::GetMeshComp()
{
	return MeshComp;
}


