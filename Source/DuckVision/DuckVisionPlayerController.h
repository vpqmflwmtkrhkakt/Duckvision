// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DuckVisionPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_MULTICAST_DELEGATE(FOnFireWeapon);

class UInputMappingContext;
class UInputAction;
class ADuckVisionCharacter;


UCLASS()
class ADuckVisionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADuckVisionPlayerController();
	virtual void OnPossess(APawn* aPawn) override;

	FOnFireWeapon OnFireWeapon;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay();

private:
	void OnGetMovementInput(const FInputActionValue& Value);
	void OnStartClickRightButton(const FInputActionValue& Value);
	void OnClickLeftButton(const FInputActionValue& Value);
	void OnClickRightButton(const FInputActionValue& Value);
	void OnPressReload(const FInputActionValue& Value);

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* LeftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* RightClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	TObjectPtr<ADuckVisionCharacter> MainPlayer;
};


