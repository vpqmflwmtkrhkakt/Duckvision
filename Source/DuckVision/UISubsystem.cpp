
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

		ScreenWidget->AddToViewport();
		ScreenWidget->SetVisibility(ESlateVisibility::Visible);

		if (IngameMenuLayerClass)
		{
			UUILayer* IngameMenuWidget = CreateWidget<UUILayer>(PC, IngameMenuLayerClass);

			if (IsValid(IngameMenuWidget))
			{
				RegisterLayer(ELayerType::IngameMenu, IngameMenuWidget);
			}
		}

	}
}

void UUISubsystem::RegisterLayer(const ELayerType LayerType, UUILayer* Layer)
{
	if (Layers.Contains(LayerType)) return;
	if (!IsValid(ScreenWidget)) return;
	
	Layers.Add(LayerType, Layer);
	ScreenWidget->RegisterLayer(Layer);
}

void UUISubsystem::PushContentToLayer(const ELayerType LayerType, UUserWidget* Content)
{
	if (!IsValid(Content)) return;
	if (!Layers.Contains(LayerType))
	{
		DebugHelper::Print("Layer Empty");
		return;
	}

	Layers[LayerType]->PushContentToLayer(Content);
}

void UUISubsystem::ClearLayer(const ELayerType LayerType)
{
	if (Layers.Contains(LayerType))
	{
		Layers[LayerType]->ClearLayer();
	}
}

void UUISubsystem::ToggleUI(const ELayerType LayerType, const UITypeEnum UIType)
{
	if (Layers.Contains(LayerType))
	{
		Layers[LayerType]->ToggleUI(UIType);
	}
}

void UUISubsystem::CloseToggleUI(const ELayerType LayerType, const UITypeEnum UIType)
{
	if (Layers.Contains(LayerType))
	{
		Layers[LayerType]->CloseToggleUI(UIType);
	}
}
