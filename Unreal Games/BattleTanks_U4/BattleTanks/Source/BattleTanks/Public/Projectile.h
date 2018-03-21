// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PhysicsEngine/RadialForceComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	UProjectileMovementComponent * ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent * CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent * LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent * ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent * ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	float DestroyDelay = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	float ProjectileDamage = 20.f;

	void OnTimerExpire();

public:	
	// Sets default values for this actor's properties
	AProjectile();
	void LaunchProjectile(float LaunchSpeed);





protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
