// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"

/*
*Component used to set patrolling points, without it ChoseNexWaypoint will not work
*/


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Patrolling")
	TArray<AActor *> PatrolPoints;

public:	
	UPatrolRoute();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<AActor *> GetPatrolPoints()const;

protected:
	virtual void BeginPlay() override;
	
	
};
