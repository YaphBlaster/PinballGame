// Fill out your copyright notice in the Description page of Project Settings.


#include "PGBumper.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
APGBumper::APGBumper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BumperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperMesh"));
	BumperMechanism = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BumperMechanism"));
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));

	// Collision Capsule height and radius setup[
	CapsuleComp->SetCapsuleHalfHeight(180.0f);
	CapsuleComp->SetCapsuleRadius(120.0f);

	// Reset all collision responses to ignore
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Specifically set collision response of PhysicsBody actors to overlap
	CapsuleComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	
	// Set the BumperMesh as the Highest Parent
	RootComponent = BumperMesh;

	// Attach the BumperMechanism and the Capsule Collision to the RootComponent (BumperMesh)
	BumperMechanism->SetupAttachment(RootComponent);
	CapsuleComp->SetupAttachment(RootComponent);

	// Initial value for the force of the bumper
	BumperForce = 2500.0f;

}

// Called when the game starts or when spawned
void APGBumper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APGBumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APGBumper::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APGBall* ball = Cast<APGBall>(OtherActor);

	if (ball)
	{
		Bump(ball);
	}

}

void APGBumper::Bump(APGBall* ball)
{
	FVector From = GetActorLocation();
	FVector To = ball->GetActorLocation();

	FVector BumperImpulse = UKismetMathLibrary::GetDirectionUnitVector(From, To) * BumperForce;
	ball->GetMeshComp()->AddImpulse(BumperImpulse, NAME_None, true);
}

