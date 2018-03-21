// Fill out your copyright notice in the Description page of Project Settings.
//custom includes
#include "../Public/TankBarrel.h"

//engine includes
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Aim rotator: %f"),DegreesPerSecond)
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	auto ElevationChange = RelativeSpeed * MaxElevationSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	


}


