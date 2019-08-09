// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGPlunger.generated.h"

class UCurveFloat;
class UTimelineComponent;

UCLASS()
class PINBALLGAME_API APGPlunger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGPlunger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		FVector BallLocation;

	/* Components needed for Timelines */
	UPROPERTY(VisibleAnywhere, Category = "Timeline")
		UTimelineComponent* PlungerTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "Timeline")
		UCurveFloat* FloatCurve;
	//--------------------------------------------------//

	UPROPERTY()
		FVector PlungerStart;

	UPROPERTY()
		FVector PlungerEnd;


	UPROPERTY()
		FLatentActionInfo LatentActionInfo;
	
	UFUNCTION()
	void Update(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChargePlunger();

	void StopCharge();

	FVector GetBallSpawnLocation();

};
