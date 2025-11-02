// Copyright Epic Games, Inc. All Rights Reserved.

#include "DuckVisionPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DebugHelper.h"
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ADuckVisionPlayerController::ADuckVisionPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ADuckVisionPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}


void ADuckVisionPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ADuckVisionPlayerController::OnGetMovementInput);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADuckVisionPlayerController::OnGetMovementInput(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();
	DebugHelper::Print("X: " + FString::SanitizeFloat(Direction.X) + " Y: " + FString::SanitizeFloat(Direction.Y));
}
