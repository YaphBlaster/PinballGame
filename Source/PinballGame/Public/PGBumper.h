// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGBall.h"
#include "PGBumper.generated.h"

class UCapsuleComponent;
class UTimelineComponent;
class UPointLightComponent;
class USoundCue;

UCLASS()
class PINBALLGAME_API APGBumper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGBumper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
		UStaticMeshComponent* BumperMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* BumperMechanism;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, Category = "Variables")
		float BumperForce;

	UPROPERTY(VisibleAnywhere, Category = "Timeline")
		UTimelineComponent* BumpTimeline;

	UPROPERTY(EditDefaultsOnly, Category ="Timeline")
		UCurveFloat* FloatCurve;

	UPROPERTY()
		FVector BumperMechanismStart;

	UPROPERTY()
		FVector BumperMechanismEnd;

	// Dynamic material
	UPROPERTY()
		UMaterialInstanceDynamic* MatInst;

	// NOTE: Audio files must be converted to Unreal's Cue format
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USoundCue* BumpSound;

	UFUNCTION()
		void Update(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Override of base function NotifyActorBeginOverlap
	// This allows us to see which Other Actors are overlapping with our Actor
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void Bump(APGBall* ball);

};
