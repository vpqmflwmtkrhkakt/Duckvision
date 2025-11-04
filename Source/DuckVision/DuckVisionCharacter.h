// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DuckVisionCharacter.generated.h"


class UAnimMontage;
UCLASS(Blueprintable)
class ADuckVisionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADuckVisionCharacter();
	//virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void StartAimToLocation();
	void RotateToTargetLocation(const FVector& Location);
	void StartReload();
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

};

