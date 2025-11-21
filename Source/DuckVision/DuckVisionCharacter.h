// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DuckVisionCharacter.generated.h"

class UAnimMontage;
class AWeapon;
class IInteractableInterface;

UCLASS(Blueprintable)
class ADuckVisionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADuckVisionCharacter();
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void StartAimToLocation();
	void RotateToTargetLocation(const FVector& Location);
	void StartReload();
<<<<<<< HEAD
<<<<<<< HEAD
	void InteractObject();
	void ToggleInventory();
=======
	void TakeCover();
>>>>>>> 34b505b (Cover Action 추가)
=======
	void TakeCover();
>>>>>>> 34b505b25072e47f6e0b706a2726fd2ffb8fd151

	UFUNCTION(BlueprintCallable)
	FTransform GetLHIKTransform();
	UFUNCTION(BlueprintCallable)
	FVector GetJoinTargetLocation();
	UFUNCTION(BlueprintCallable)
	void SetInteractableObject(UObject* Object);

	UFUNCTION(BlueprintCallable)
	UObject* GetInteractableObject();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere, Category = MovementSpeed, meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 600.f;

	FRotator LastRotation;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> WeaponClass;

	TObjectPtr<AWeapon> EquippedWeapon;

	TWeakObjectPtr<UObject> InteractableObject;
};

