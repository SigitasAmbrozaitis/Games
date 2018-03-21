// Fill out your copyright notice in the Description page of Project Settings.

//custom includes
#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/Projectile.h"

//engine includes
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSecond)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else if(Ammunition == 0)
	{
		FiringState = EFiringStatus::OutOfAmmo;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
	//TODO handle aiming and locked states
}


void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

EFiringStatus UTankAimingComponent::GetFiringState()const
{
	return FiringState;
}
int32 UTankAimingComponent::GetAmmunition() const
{
	return Ammunition;
}
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName(TEXT("Projectile")));


	//calculate the out launch velocity
	if	(!UGameplayStatics::SuggestProjectileVelocity
			(
				this,
				LaunchVelocity,
				StartLocation,
				HitLocation,
				LaunchSpeed,
				false,
				0.f,
				0.f,
				ESuggestProjVelocityTraceOption::DoNotTrace
			)
	) {	return;	}

	
	AimDirection = LaunchVelocity.GetSafeNormal();
	
	
	MoveBarrel();
	MoveTurret();


}

void UTankAimingComponent::InitializeTurret(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	if (!ensure(TurretToSet)) { UE_LOG(LogTemp, Error, TEXT("No Turret")); return; }
	if (!ensure(BarrelToSet)) { UE_LOG(LogTemp, Error, TEXT("No Barrel")); return; }
	Turret = TurretToSet;
	Barrel = BarrelToSet;

}



void UTankAimingComponent::MoveBarrel()
{
	if (!ensure(Barrel)) { return; }
	
	//work out current battle direction and aim direction
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	//move barrel altitude (maxspeed)
	Barrel->Elevate(DeltaRotation.Pitch);

	
}

void UTankAimingComponent::MoveTurret()
{
	if (!ensure(Turret)) { return; }
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - TurretRotation;


	// 1: * Get turret rotation from tank perspetive(currently its from world perspective)
	// 2: Fix unwanted behavior when rotation transfers from -180 to 180 and vice versa
	//    Idea: Calcluate ABS of rotation WORKING AS INTENDED
	float Factor1 = FMath::Abs<float>(DeltaRotation.Yaw);
	float Factor2 = FMath::Abs<float>(DeltaRotation.Yaw+360);
	float Factor3 = FMath::Abs<float>(DeltaRotation.Yaw-360);

	if (Factor3 < Factor2  && Factor3 < Factor1)
	{
		DeltaRotation.Yaw = DeltaRotation.Yaw - 360;
	}
	else if (Factor2 < Factor3 && Factor2 < Factor1)
	{
		DeltaRotation.Yaw = DeltaRotation.Yaw + 360;
	}
	//******************************************************Do not Change
	Turret->Rotate(DeltaRotation.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	

	return !BarrelForward.Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }
	if (Ammunition == 0) {/* FiringState = EFiringStatus::OutOfAmmo; */return; }
	//bool isReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecond);
	
	

	if (FiringState!=EFiringStatus::Reloading)
	{
		Ammunition--;
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName(TEXT("Projectile"))),
			Barrel->GetSocketRotation(FName(TEXT("Projectile")))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	//Spawn Projectile at socket location


}


