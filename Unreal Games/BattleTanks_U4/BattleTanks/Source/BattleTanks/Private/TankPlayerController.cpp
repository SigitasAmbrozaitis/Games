// Fill out your copyright notice in the Description page of Project Settings.

//custom includes
#include "../Public/TankPlayerController.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/Tank.h"

//engine includes
#include "Engine/World.h"
#include "GameFramework/Actor.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { UE_LOG(LogTemp, Error, TEXT("No Aiming Component in Player Controller")) return; }

	FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
	
}


void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation; //out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}else {	return;	}

	

	///Get world location if linetrace 
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	
	//Find crosshair position
	FVector2D ScreenLocation;
	int32 ViewportSizeX, ViewportSizeY;
	this->GetViewportSize(ViewportSizeX, ViewportSizeY);

	ScreenLocation.X = ((float)ViewportSizeX) * CrossHairXLocation;
	ScreenLocation.Y = ((float)ViewportSizeY) * CrossHairYLocation;

	//de-project the screen position of the crosshair to a world direction
	FVector WorldDirrection;
	if (!ensure(GetLookDirrection(ScreenLocation, WorldDirrection))) { return false; }
	
	//line trace along to see what we hit
	if (!GetHitLocation(HitLocation, WorldDirrection)) { return false; }



	return true;
}

bool ATankPlayerController::GetLookDirrection(FVector2D ScreenLocation, FVector & WorldDirrection) const
{
	FVector WorldLocation;
	
	if (!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirrection))
	{
		return false;
	}
	return true;
}

bool ATankPlayerController::GetHitLocation(FVector & HitLocation, FVector WorldDirrection) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (WorldDirrection * HitRange);

	if (GetWorld()->LineTraceSingleByChannel
		(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
	){
		HitLocation  = HitResult.Location;
		return true;

	}

	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{

	Super::SetPawn(InPawn);

	if (!InPawn) { return; }
	auto PossesedTank = Cast<ATank>(InPawn);
	if (!ensure(PossesedTank)) { return; }
	PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedTankDeath);

}

void ATankPlayerController::OnPossesedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank Died"))
	StartSpectatingOnly();
}