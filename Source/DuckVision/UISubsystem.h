// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubsystem.generated.h"

enum class ELayerType : uint32
{
	HUD,
	IngameMenu,
	Menu,
	Popup
};

class UUILayer;
class UScreenWidget;
UCLASS()
class DUCKVISION_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UUISubsystem();
	void InitializeUI(APlayerController* PC);
	void RegisterLayer(const ELayerType UIType, UUILayer* Layer);
	void PushContentToLayer(const ELayerType UIType, UUserWidget* Content);
	void ClearLayer(const ELayerType UIType);

private:
	TSubclassOf<UUserWidget> ScreenLayerClass;
	TSubclassOf<UUserWidget> IngameMenuLayerClass;
	UScreenWidget* ScreenWidget;
	TMap<ELayerType, UUILayer*> Layers;
};
