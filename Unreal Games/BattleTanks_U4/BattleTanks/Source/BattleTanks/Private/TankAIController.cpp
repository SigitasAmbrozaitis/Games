// Fill out your copyright notice in the Description page of Project Settings.

//custom includes
#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/Tank.h"

//engine includes
#include "GameFramework/Actor.h"
#include "Engine/World.h"



ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	UTankAimingComponent * AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	if (!ensure(PlayerTank)) { return; }

	//TODO MoveTowardsPlayer
	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//TODO fix firing
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}

}

void ATankAIController::SetPawn(APawn * InPawn)
{

	Super::SetPawn(InPawn);

	if (!InPawn) { return; }
	auto PossesedTank = Cast<ATank>(InPawn);
	if (!ensure(PossesedTank)) { return; }

	//TODO Subscribe to Tanks death event
	PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);

}

void ATankAIController::OnPossesedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank Died"))
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();

}
