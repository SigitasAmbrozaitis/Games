// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetUpInputComponent();
	// ...
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	///Look for PhysicsHandle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle ==nullptr)
	{
		FString Error = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("%s PhysicsHandle is missing"), *Error);
	}
}

void UGrabber::SetUpInputComponent()
{	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		///bind input axis
		InputComponent->BindAction("Grab", IE_Pressed,  this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no InputController"), *(GetOwner()->GetName()));
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///Setup Querry parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///Ray-cast out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	return LineTraceHit;
}

const FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

const FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector()*Range);
}

const FRotator UGrabber::GetReachLineRotation()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	return PlayerViewPointRotation;
}

void UGrabber::Grab()
{
	///try and reach any actor with physics collision channel  set
	FHitResult HitResult  = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent * ComponentToGrab = HitResult.GetComponent();
	AActor * ActorHit = HitResult.GetActor();
	///if we hit smth attach the physics handle
	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None, //no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			GetReachLineRotation() //rotation
		);	
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}
