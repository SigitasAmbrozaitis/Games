// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	IsOpen = false;
	Owner = GetOwner();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor: %s has no PressurePlate assigned"), *Owner->GetName());
	}

	// ...
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll Trggger volume
	if (GetTotallMassOfActorOnPlate() >= TriggerMass)
	{
		OpenRequest.Broadcast();
	}
	else
	{
		CloseRequest.Broadcast();
	}
	// ...
}

float UOpenDoor::GetTotallMassOfActorOnPlate()
{
	float TotalMass = 0.f;

	
	//check if there is PressurePlate to begin with
	if (!PressurePlate) { return 0.f; }
	
	//find all overlapping actors with pressure plate
	TArray<AActor *> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//iterate through them adding their masses
	for (const auto & Actor : OverlappingActors)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Object name: %s)", *(Actor->GetName());
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("Object on pressure plate: %s"), *Actor->GetName());
	}


	return TotalMass;
}