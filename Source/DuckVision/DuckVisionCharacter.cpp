// Copyright Epic Games, Inc. All Rights Reserved.

#include "DuckVisionCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "DebugHelper.h"
#include "Weapon.h"
#include "InteractableInterface.h"
#include "InventoryComponent.h"

ADuckVisionCharacter::ADuckVisionCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	ConstructorHelpers::FClassFinder<AWeapon> WeaponClassFinder(TEXT("/Game/DuckVision/Blueprints/BP_Weapon"));

	if (WeaponClassFinder.Succeeded())
	{
		WeaponClass = WeaponClassFinder.Class;
	}
	else
	{
		DebugHelper::Print("Find WeaponClass Failed");
	}

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ADuckVisionCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponClass)
	{
		EquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);

		if (IsValid(EquippedWeapon))
		{
			EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_socket"));

			EquippedWeapon->SetupWeapon(this);

			EquippedWeapon->SetActorRelativeLocation(FVector(-6.875157, 2.168866, 14.445861));
			FRotator Rotator(27.968352, -168.20965, 4.126927);
			EquippedWeapon->SetActorRelativeRotation(Rotator);
			//(Pitch = 27.968352, Yaw = -168.209650, Roll = 4.126927)
		}
	}
}


void ADuckVisionCharacter::StartAimToLocation()
{
	LastRotation = GetActorRotation();
}

void ADuckVisionCharacter::RotateToTargetLocation(const FVector& Location)
{
	FVector ToLocationDirection = Location - GetActorLocation();

	ToLocationDirection.Z = 0.f;

	if (ToLocationDirection.IsNearlyZero()) return;

	FRotator TargetRotation = ToLocationDirection.Rotation();

	const float RotationSpeed = 10.f;

	FRotator NewRotation = FMath::RInterpTo(LastRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);

	SetActorRotation(NewRotation);

	LastRotation = NewRotation;
}

void ADuckVisionCharacter::StartReload()
{
	if (!ReloadAnimMontage) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (!AnimInstance) return;

	AnimInstance->Montage_Play(ReloadAnimMontage);
}

void ADuckVisionCharacter::InteractObject()
{
	if (!InteractableObject.IsValid()) return;

	IInteractableInterface* Object = Cast<IInteractableInterface>(InteractableObject.Get());
	if (Object)
	{
		Object->Interact(this);
	}
}

void ADuckVisionCharacter::ToggleInventory()
{
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->ToggleInventory();
	}
}

FTransform ADuckVisionCharacter::GetLHIKTransform()
{
	if (!IsValid(EquippedWeapon)) return FTransform();

	FTransform WeaponTransform = EquippedWeapon->GetSocketTransform();

	FVector Location;
	FRotator Rotation;

	GetMesh()->TransformToBoneSpace(TEXT("weapon_r"), WeaponTransform.GetLocation(), WeaponTransform.Rotator(), Location, Rotation);

	return FTransform(Rotation, Location, FVector(1,1,1));
}

FVector ADuckVisionCharacter::GetJoinTargetLocation()
{
	if (!IsValid(EquippedWeapon)) return FVector::ZeroVector;

	return EquippedWeapon->GetJointTargetLocation();
}

void ADuckVisionCharacter::SetInteractableObject(IInteractableInterface* Object)
{
	InteractableObject = Cast<UObject>(Object);
}

IInteractableInterface* ADuckVisionCharacter::GetInteractableObject()
{
	if (InteractableObject.IsValid())
	{
		return Cast<IInteractableInterface>(InteractableObject.Get());
	}

	return nullptr;
}

