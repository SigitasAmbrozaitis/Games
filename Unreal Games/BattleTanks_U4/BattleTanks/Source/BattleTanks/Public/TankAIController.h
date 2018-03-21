// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;



UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 5000.f;

	virtual void SetPawn(APawn * InPawn)override;

	UFUNCTION()
	void OnPossesedTankDeath();

	
public:
	UTankAimingComponent * AimingComponent = nullptr; //refactoring
	ATankAIController();
	virtual void BeginPlay() override;
protected:
	
	virtual void Tick(float DeltaTime)override;

	
};
