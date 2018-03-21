// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
	Score = 0;
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerrainGameMode::IncreaseScore()
{
	++Score;
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), Score);
}

int32 AInfiniteTerrainGameMode::GetScore()const
{
	return Score;
}


void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}



