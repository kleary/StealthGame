// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class STEALTHGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:

	UPROPERTY(VisibleAnywhere, Category = Overlap)
	class UBoxComponent* OverlapComponent;

	UPROPERTY(VisibleAnywhere, Category = StaticMesh)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditInstanceOnly, Category = LaunchPad)
	float LaunchStrength = 1500;

	UPROPERTY(EditInstanceOnly, Category = LaunchPad)
	float LaunchPitchAngle = 35.0f;

	UPROPERTY(EditDefaultsOnly, Category = LaunchPad)
	class UParticleSystem* ActivateLaunchPadEffect;

	UFUNCTION()
		void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
