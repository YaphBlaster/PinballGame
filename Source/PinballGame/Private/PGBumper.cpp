// Fill out your copyright notice in the Description page of Project Settings.


#include "PGBumper.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include <Components/TimelineComponent.h>

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
APGBumper::APGBumper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BumperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperMesh"));
	BumperMechanism = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BumperMechanism"));
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	BumpTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));



	// Collision Capsule height and radius setup
	CapsuleComp->SetCapsuleHalfHeight(180.0f);
	CapsuleComp->SetCapsuleRadius(120.0f);

	// Reset all collision responses to ignore
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Specifically set collision response to PhysicsBody actors to overlap
	CapsuleComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	
	// Set the BumperMesh as the Highest Parent
	RootComponent = BumperMesh;

	// Attach the BumperMechanism and the Capsule Collision to the RootComponent (BumperMesh)
	BumperMechanism->SetupAttachment(RootComponent);
	CapsuleComp->SetupAttachment(RootComponent);

	// Since the material is upside down, we must create a new rotator with a Yaw of 180.0f;
	FRotator NewRotation = FRotator(0, 180.0f, 0);

	// Set the Actor's(this Bumper) rotation to the NewRotation above
	SetActorRotation(NewRotation);

	// Initial value for the force of the bumper
	BumperForce = 2500.0f;

}

// Called when the game starts or when spawned
void APGBumper::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat InterpFunc;


	// Check if curve asset reference is valid
	if (FloatCurve)
	{
		InterpFunc.BindUFunction(this, FName("Update"));

		// Add the float curve to the Timeline and connect to the InterpFunction's delegate
		BumpTimeline->AddInterpFloat(FloatCurve, InterpFunc, FName("Alpha"));

		// Setting Vectors
		BumperMechanismStart = FVector();
		BumperMechanismEnd = FVector(0.0f, 0.0f, -70.0f);

		// Setting our TimeLine's settings before we start it
		BumpTimeline->SetLooping(false);
		BumpTimeline->SetIgnoreTimeDilation(true);
	}
	
}

void APGBumper::Update(float value)
{
	BumperMechanism->SetRelativeLocation(FMath::Lerp(BumperMechanismStart, BumperMechanismEnd, value));
}

// Called every frame
void APGBumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APGBumper::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Cast the overlapping actor to the PGBall class
	auto ball = Cast<APGBall>(OtherActor);

	// If the casted actor was indeed a PGBall
	if (ball)
	{
		// Bump the ball
		Bump(ball);
	}
}

void APGBumper::Bump(APGBall* ball)
{
	// Vector of the Bumper's current location
	FVector From = GetActorLocation();

	// Vector of the ball's location
	FVector To = ball->GetActorLocation();

	// The direction the ball will be sent
	FVector BumpDirection = UKismetMathLibrary::GetDirectionUnitVector(From, To);

	// Add an impulse to the ball equaling the BumpDirection multiplied by the BumpForce
	// It's necessary to multiply by the BumpForce because GetDirectionUnitVector simply gives the direction and the actual force will be minimal
	ball->GetMeshComp()->AddImpulse(BumpDirection * BumperForce, NAME_None, true);

	// Play TimeLine
	BumpTimeline->PlayFromStart();
}

