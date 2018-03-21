// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//enum for aiming state
UENUM()
enum class EFiringStatus :uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};




class AProjectile;
class UTankTurret;
class UTankBarrel;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSecond = 3.f;


	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 Ammunition = 20.f;

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;



public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InitializeTurret(UTankTurret * TurretToSet, UTankBarrel  * BarrelToSet);

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmunition()const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringStatus FiringState = EFiringStatus::Reloading;
private:

	double LastFireTime = 0;
	FVector AimDirection;
	void MoveBarrel();
	void MoveTurret();
	bool IsBarrelMoving();
	
};
