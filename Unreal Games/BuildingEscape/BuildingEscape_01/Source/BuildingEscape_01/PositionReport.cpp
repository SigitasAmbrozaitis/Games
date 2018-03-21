// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	
	Object = GetOwner();
	if (!Object) { return; }
	FString ObjectName = Object->GetName();
	FVector ObjectLocation = Object->GetActorLocation();


	UE_LOG(LogTemp, Warning, TEXT(" %s constructed, at (%f,%f,%f)"), *ObjectName, ObjectLocation.X, ObjectLocation.Y, ObjectLocation.Z);


	// ...
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

