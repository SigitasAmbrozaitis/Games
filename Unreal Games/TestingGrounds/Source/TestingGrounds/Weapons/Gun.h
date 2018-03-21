// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()
		
	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* FP_Gun;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;


public:	
	// Sets default values for this actor's properties
	AGun();

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* FireAnimationTP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* FireAnimationFP;

	UPROPERTY()
	class UAnimInstance* AnimInstanceTP;

	UPROPERTY()
	class UAnimInstance* AnimInstanceFP;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABallProjectile> ProjectileClass;


	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnFire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	




};
