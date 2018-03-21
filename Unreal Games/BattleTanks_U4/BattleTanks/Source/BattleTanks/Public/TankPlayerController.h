// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;



UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
	float HitRange = 1000000.f;

	virtual void SetPawn(APawn * InPawn)override;

	UFUNCTION()
	void OnPossesedTankDeath();

public:
	ATankPlayerController();
	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime)override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent * AimingComponentReference);

private:

	void AimTowardCrosshair();
	bool GetSightRayHitLocation(FVector & HitLocation) const;
	bool GetLookDirrection(FVector2D ScreenLocation, FVector & WorldDirrection) const;
	bool GetHitLocation(FVector & HitLocation, FVector WorldDirrection) const;
	
};
