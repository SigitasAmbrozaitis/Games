// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsVolumePool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score;

public:
	AInfiniteTerrainGameMode();
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void IncreaseScore();
	int32 GetScore()const;
private:
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
	
	
};
