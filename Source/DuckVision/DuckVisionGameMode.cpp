// Copyright Epic Games, Inc. All Rights Reserved.

#include "DuckVisionGameMode.h"
#include "DuckVisionPlayerController.h"
#include "DuckVisionCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADuckVisionGameMode::ADuckVisionGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADuckVisionPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DuckVision/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/DuckVision/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}