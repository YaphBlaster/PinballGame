// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGBallResetZone.generated.h"

class UBoxComponent;

UCLASS()
class PINBALLGAME_API APGBallResetZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGBallResetZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Override of base function NotifyActorBeginOverlap
	// This allows us to see which Other Actors are overlapping with our Actor
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
