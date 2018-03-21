// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack)) { return; }
	if (!ensure(RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!ensure(LeftTrack)) { return; }
	if (!ensure(RightTrack)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Right: %f"), Throw)
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
void UTankMovementComponent::IntendRotateAntiClockwise(float Throw)
{
	if (!ensure(LeftTrack)) { return; }
	if (!ensure(RightTrack)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Left: %f"), Throw)
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::InitializeTracks(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!ensure(LeftTrackToSet)) { UE_LOG(LogTemp, Warning, TEXT("No LeftTrack")); return; }
	if (!ensure(RightTrackToSet)) { UE_LOG(LogTemp, Warning, TEXT("No RightTrack")); return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

	
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity,bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto IntendRotation = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));
	IntendRotateClockwise(IntendRotation.Z);
}

