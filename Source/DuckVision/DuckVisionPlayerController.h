// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DuckVisionPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ADuckVisionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADuckVisionPlayerController();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay();

private:
	void OnGetMovementInput(const FInputActionValue& Value);

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MovementAction;

};


