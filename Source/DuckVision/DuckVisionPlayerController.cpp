// Copyright Epic Games, Inc. All Rights Reserved.

#include "DuckVisionPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DebugHelper.h"
#include "DuckVisionCharacter.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ADuckVisionPlayerController::ADuckVisionPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ADuckVisionPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (IsValid(aPawn))
	{
		MainPlayer = Cast<ADuckVisionCharacter>(aPawn);
	}
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


		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &ADuckVisionPlayerController::OnClickRightButton);

		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Triggered, this, &ADuckVisionPlayerController::OnClickRightButton);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADuckVisionPlayerController::OnGetMovementInput(const FInputActionValue& Value)
{
	FVector Direction = Value.Get<FVector>();

	ACharacter* PossessedCharacter = GetCharacter();

	if (IsValid(PossessedCharacter))
	{
		PossessedCharacter->AddMovementInput(Direction.GetSafeNormal());
	}
}

void ADuckVisionPlayerController::OnStartClickRightButton(const FInputActionValue& Value)
{
	if (!IsValid(MainPlayer)) return;

	MainPlayer->StartAimToLocation();
}

void ADuckVisionPlayerController::OnClickRightButton(const FInputActionValue& Value)
{
	if (!IsValid(MainPlayer)) return;

	FHitResult HitResult;

	if (GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, true, HitResult))
	{
		MainPlayer->RotateToTargetLocation(HitResult.ImpactPoint);
	}
}
