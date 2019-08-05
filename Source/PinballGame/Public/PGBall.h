// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGBall.generated.h"

UCLASS()
class PINBALLGAME_API APGBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variables")
		FVector DefaultSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variables")
		float TableStickyness;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
