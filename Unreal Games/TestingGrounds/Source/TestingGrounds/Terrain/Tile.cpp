// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
//#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Core/Public/Math/TransformCalculus3D.h"
#include "ActorPool.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"

FSpawnPosition::FSpawnPosition(FVector SpawnLocation, FRotator SpawnRotation, FVector SpawnScale)
{
	Location = SpawnLocation;
	Rotation = SpawnRotation;
	Scale = SpawnScale;
}
FSpawnPosition::FSpawnPosition(){}
// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MinSpawnExtent=FVector(0.f, -2000.f, 0.f);
	MaxSpawnExtent=FVector(4000.f, 2000.f, 0.f);
	NavigationBoundsOffset = FVector(2000.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	//PlaceActors();
	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CastSphere(GetActorLocation(), 300);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, int32 RotationPositions, float MinScale, float MaxScale)
{
	PlaceRandomActors(ToSpawn,MinSpawn, MaxSpawn, Radius, RotationPositions, MinScale, MaxScale);


}
void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, int32 RotationPositions)
{
	PlaceRandomActors(ToSpawn,MinSpawn, MaxSpawn, Radius, RotationPositions, 1, 1);
}

template<class T>
void ATile::PlaceRandomActors(TSubclassOf<T> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, int32 RotationPositions, float MinScale, float MaxScale)
{
	FVector SpawnLocation;
	FVector SpawnScale;
	FRotator SpawnRotation;

	int32 NumberToGenerate = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int32 i = 0; i < NumberToGenerate; ++i)
	{
		bool FoundLocation = false;

		for (int j = 0; j < 100; ++j)
		{
			float Scale = GetRandomScale(MinScale, MaxScale);
			SpawnScale = FVector(Scale);

			SpawnLocation = GetEmptyLocation(Radius*Scale);
			if (!SpawnLocation.Equals(FVector(0, 0, 0), 0.1)) { FoundLocation = true; break; }
		}

		if (FoundLocation)
		{
			FRotator SpawnRotation = GetRandomRotation(RotationPositions);
			FSpawnPosition SpawnPosition(SpawnLocation, SpawnRotation, SpawnScale);
			PlaceActor(ToSpawn, SpawnPosition);
		}
	}
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	APawn * Spawned = Cast<APawn>(GetWorld()->SpawnActor(ToSpawn, &SpawnPosition.Location, &SpawnPosition.Rotation));
	if (!Spawned) { return; }
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	/*Spawned->SetActorRelativeLocation();
	Spawned->SetActorRotation();
	Spawned->SetActorRelativeScale3D(SpawnPosition.Scale);*/

	Spawned->Tags.Add(FName("Enemy"));
	Spawned->SpawnDefaultController();
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	AActor * Spawned = GetWorld()->SpawnActor(ToSpawn);
	if (!Spawned) { return; }
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->SetActorRotation(SpawnPosition.Rotation);
	Spawned->SetActorRelativeScale3D(SpawnPosition.Scale);
}

void ATile::SetPool(UActorPool * Pool)
{
	if (!Pool) { return; }
	this->Pool = Pool;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (!NavMeshBoundsVolume) { UE_LOG(LogTemp, Error, TEXT("No NavMesh to Give")) return; }
	UE_LOG(LogTemp, Warning, TEXT("Giving: %s"), *NavMeshBoundsVolume->GetName())
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}



bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	Location = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	FColor HitColor = (HasHit) ? FColor::Red : FColor::Green;

	//DrawDebugSphere(GetWorld(), Location, Radius, 16, HitColor, true, 100);
	
	return HasHit;
}

FVector ATile::GetEmptyLocation(float Radius)
{

	FBox SpawnBounds(MinSpawnExtent, MaxSpawnExtent);
	FVector SpawnPoint = FMath::RandPointInBox(SpawnBounds);
	
	if (!CastSphere(SpawnPoint, Radius))
	{
		return SpawnPoint;

	}
	else { SpawnPoint = FVector(0, 0, 0); }

	return SpawnPoint;
}





FRotator ATile::GetRandomRotation(int32 RotationPositions)
{
	int32 RotationMultiplier = FMath::RandRange(0, RotationPositions-1);
	FRotator SpawnRotation(0.f, (float)RotationMultiplier*(360/RotationPositions), 0.f);
	return SpawnRotation;
}

float ATile::GetRandomScale(float MinScale, float MaxScale)
{
	float ScaleMultiplier = FMath::RandRange(MinScale, MaxScale);
	return  ScaleMultiplier;
}

