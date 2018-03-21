// Fill out your copyright notice in the Description page of Project Settings.

//custom includes
#include "../Public/Tank.h"
//#include "../Public/TankMovementComponent.h"

//engine includes
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = TankHealth;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoint = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth == 0) { OnDeath.Broadcast(); }
	
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)TankHealth;
}

