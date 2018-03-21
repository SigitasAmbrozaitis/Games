// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_01_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPhysicsHandleComponent * PhysicsHandle = nullptr;
	UInputComponent * InputComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float Range = 150.f;

	//sets PhysicsHandle 
	void FindPhysicsHandleComponent();

	//set InputController
	void SetUpInputComponent();

	//return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//return current start of reach line
	const FVector GetReachLineStart();
	
	//return current end of reach line
	const FVector GetReachLineEnd();

	//return current rotation of reach line
	const FRotator GetReachLineRotation();

	///ray cast and grab
	void Grab();
	void Release();
	

};
