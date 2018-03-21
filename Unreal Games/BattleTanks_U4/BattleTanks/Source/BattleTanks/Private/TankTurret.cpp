// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTurret.h"

//engine includes
#include "Engine/World.h"

void UTankTurret::Rotate(float RotationSpeed)
{
	RotationSpeed = FMath::Clamp<float>(RotationSpeed, -1.f, 1.f);

	auto RotationChange = RotationSpeed * MaxRotationSpeed * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}

