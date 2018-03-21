// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 TankHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	int32 CurrentHealth = TankHealth;

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser)override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const ;

	FTankDelegate OnDeath;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
