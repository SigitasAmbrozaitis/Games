// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTrack.h"

#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);



}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;

}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle+Throttle, -1.f, 1.f);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
	
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlidingSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAccelaration = -SlidingSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass()*CorrectionAccelaration / 2;
	TankRoot->AddForce(CorrectionForce);
}