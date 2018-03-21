// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"
class FScale;

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	FRotator Rotation;
	FVector Scale;
	FSpawnPosition(FVector SpawnLocation, FRotator SpawnRotation, FVector SpawnScale);
	FSpawnPosition();
};






UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	class UActorPool * Pool;

	class ANavMeshBoundsVolume * NavMeshBoundsVolume;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinSpawnExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxSpawnExtent;

	TArray<AActor*> Spawns;

public:	
	// Sets default values for this actor's properties
	ATile();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1,float Radius = 500, int32 RotationPositions=4, float MinScale = 1.f, float MaxScale = 1.f);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, int32 RotationPositions = 4);


	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(class UActorPool * Pool);

	

protected:

private:
	bool CastSphere(FVector Location, float Radius);
	FVector GetEmptyLocation(float Radius);
	
	FRotator GetRandomRotation(int32 RotationPositions);
	float GetRandomScale(float MinScale, float MaxScale);
	void PositionNavMeshBoundsVolume();

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	template<class T>
	void PlaceRandomActors(TSubclassOf<T> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, int32 RotationPositions = 4, float MinScale=1, float MaxScale=1);
};


