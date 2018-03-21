// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"


/**
 *Chooses next patrol point for AI to travel to(PatrolRoute Component is needed) 
 */

UCLASS()
class TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackborad")
	struct FBlackboardKeySelector IndexKey;

	UPROPERTY(EditAnywhere, Category = "Blackborad")
	struct FBlackboardKeySelector WaypointKey;


};
