// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h" //always last

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);







UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_01_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	///Pointers******************************
	AActor * Owner = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate = nullptr;
	///**************************************
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent CloseRequest;



	bool IsOpen;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;


	// Called when the game starts
	virtual void BeginPlay() override;


	float LastDoorOpenTime;
	float GetTotallMassOfActorOnPlate();
	
};
