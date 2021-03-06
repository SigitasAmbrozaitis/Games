// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"
class UTankTrack;
/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;

	//called from path finding logic by AI controllers
	virtual void RequestDirectMove(const FVector & MoveVelocity,bool bForceMaxSpeed) override;


public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendRotateClockwise(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendRotateAntiClockwise(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InitializeTracks(UTankTrack * LefTTrackToSet, UTankTrack * RightTrackToSet);
	

	
};
