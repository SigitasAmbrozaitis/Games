// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving speed and aply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()



	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 4000000.f;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	float CurrentThrottle = 0.f;

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Speed);

	void DriveTrack();

	UTankTrack();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ApplySidewaysForce();
protected:
	virtual void BeginPlay() override;

	
};
