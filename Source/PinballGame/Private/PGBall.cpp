// Fill out your copyright notice in the Description page of Project Settings.


#include "PGBall.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APGBall::APGBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	
	RootComponent = MeshComp;

	DefaultSpeed = FVector(0.0f, -2000.0f, 0.0f);

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

	MeshComp->AddImpulse(DefaultSpeed * DeltaTime, NAME_None, true);

}

