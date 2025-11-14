
#include "UISubsystem.h"
#include "Blueprint/UserWidget.h"
#include "UILayer.h"
#include "DebugHelper.h"
#include "ScreenWidget.h"

UUISubsystem::UUISubsystem()
{
	ConstructorHelpers::FClassFinder<UUserWidget> ScreenLayerFinder(TEXT("/Game/DuckVision/Blueprints/UI/WBP_Screen"));

	if (ScreenLayerFinder.Succeeded())
	{
		ScreenLayerClass = ScreenLayerFinder.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> IngameMenuLayerFinder(TEXT("/Game/DuckVision/Blueprints/UI/Layers/WBP_IngameMenuLayer"));
	if (IngameMenuLayerFinder.Succeeded())
	{
		IngameMenuLayerClass = IngameMenuLayerFinder.Class;
	}

}

void UUISubsystem::InitializeUI(APlayerController* PC)
{
	DebugHelper::Print("Init ui");
	if (!IsValid(PC))
	{
		DebugHelper::Print("PC Not Exists");
		return;
	}

	if (ScreenLayerClass)
	{
		ScreenWidget = CreateWidget<UScreenWidget>(PC, ScreenLayerClass);

		if (!IsValid(ScreenWidget))
		{
			DebugHelper::Print("Failed To Create ScreenLayerWidget");
			return;
		}

		if (IngameMenuLayerClass)
		{
			UUILayer* IngameMenuWidget = CreateWidget<UUILayer>(PC, IngameMenuLayerClass);

			if (IsValid(IngameMenuWidget))
			{
				RegisterLayer(EUIType::IngameMenu, IngameMenuWidget);
			}
		}

		ScreenWidget->AddToViewport();
	}
}

void UUISubsystem::RegisterLayer(const EUIType UIType, UUILayer* Layer)
{
	if (Layers.Contains(UIType)) return;

	Layers.Add(UIType, Layer);
	
	if (IsValid(ScreenWidget))
	{
		ScreenWidget->RegisterLayer(Layer);
	}
}

void UUISubsystem::PushContentToLayer(const EUIType UIType, UUserWidget* Content)
{
	//if (!IsValid(Content)) return;
	if (!Layers.Contains(UIType))
	{
		DebugHelper::Print("Layer Empty");
		return;
	}

	Layers[UIType]->PushContentToLayer(Content);
}

void UUISubsystem::ClearLayer(const EUIType UIType)
{
	if (Layers.Contains(UIType))
	{
		Layers[UIType]->ClearLayer();
	}
}
