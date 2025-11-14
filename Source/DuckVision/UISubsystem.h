// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubsystem.generated.h"

enum class EUIType : uint32
{
	HUD,
	IngameMenu,
	Menu,
	Popup
};

class UUILayer;

UCLASS()
class DUCKVISION_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUISubsystem();
	void InitializeUI(APlayerController* PC);
	//void RegisterLayer(const EUIType UIType, ULayer);
	void PushContentToLayer(const EUIType UIType, UUserWidget* Content);
	void ClearLayer(const EUIType UIType);

private:
	TSubclassOf<UUserWidget> ScreenLayerClass;

	TMap<EUIType, UUILayer*> Layers;
};
