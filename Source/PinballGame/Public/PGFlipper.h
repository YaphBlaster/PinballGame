// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGFlipper.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EFlipperType : uint8
{
	FT_Left 	UMETA(DisplayName = "Left"),
	FT_Right 	UMETA(DisplayName = "Right"),
};

UCLASS()
class PINBALLGAME_API APGFlipper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGFlipper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Rotation")
		FRotator StartRotation;

	UPROPERTY(VisibleAnywhere, Category = "Rotation")
		FRotator EndRotation;

	UPROPERTY(VisibleAnywhere, Category = "Rotation")
		FVector Scale;

	UPROPERTY(EditAnywhere, Category = "Flipper Position")
		EFlipperType FlipperType;

	UPROPERTY()
		FLatentActionInfo LatentActionInfo;

	UPROPERTY(EditAnywhere, Category = "Flipper Position")
		float FlipTime;

	UFUNCTION(BlueprintCallable, Category = "Custom Functions")
		void SetDefaults();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EFlipperType GetFlipperType();

	UFUNCTION(BlueprintCallable, Category = "Custom Functions")
		void Flip();

	UFUNCTION(BlueprintCallable, Category = "Custom Functions")
		void Flop();
};
