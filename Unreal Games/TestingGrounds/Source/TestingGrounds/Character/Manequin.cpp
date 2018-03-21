// Fill out your copyright notice in the Description page of Project Settings.

#include "Manequin.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "../Weapons/Gun.h"

// Sets default values
AManequin::AManequin()
{
	//auto Capsule = Cast<USceneComponent>(GetCapsuleComponent());
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FP_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FP_Camera"));
	FP_Camera->SetupAttachment(RootComponent);
	FP_Camera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FP_Camera->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FP_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Arms"));
	FP_Arms->SetOnlyOwnerSee(true);
	FP_Arms->SetupAttachment(FP_Camera);
	FP_Arms->bCastDynamicShadow = false;
	FP_Arms->CastShadow = false;
	FP_Arms->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FP_Arms->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	
}

// Called when the game starts or when spawned
void AManequin::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GunBlueprint)) { return; }
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);

	if(!Gun) { UE_LOG(LogTemp, Error, TEXT("No Gun")) return; }
	if (IsPlayerControlled())
	{
		Gun->AttachToComponent(FP_Arms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{	
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));	
	}
	Gun->AnimInstanceFP = FP_Arms->GetAnimInstance();
	Gun->AnimInstanceTP = GetMesh()->GetAnimInstance();

	if (!InputComponent) { return; }
	InputComponent->BindAction("Fire", IE_Pressed, this, &AManequin::PullTrigger);

}

// Called every frame
void AManequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AManequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AManequin::PullTrigger()
{
	if (!Gun) { UE_LOG(LogTemp, Error, TEXT("No Gun")) return; }
	Gun->OnFire();
}

void AManequin::UnPossessed()
{
	//Super::UnPossessed();
	if (!Gun) { UE_LOG(LogTemp, Error, TEXT("No Gun")) return; }
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));


}

 