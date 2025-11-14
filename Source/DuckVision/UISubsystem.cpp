
#include "UISubsystem.h"
#include "Blueprint/UserWidget.h"
#include "UILayer.h"
#include "DebugHelper.h"

UUISubsystem::UUISubsystem()
{
	ConstructorHelpers::FClassFinder<UUserWidget> Finder(TEXT("/Game/DuckVision/Blueprints/UI/WBP_Screen"));

	if (Finder.Succeeded())
	{
		ScreenLayerClass = Finder.Class;
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
		UUserWidget* ScreenLayerWidget = CreateWidget<UUserWidget>(PC, ScreenLayerClass);

		if (!IsValid(ScreenLayerWidget))
		{
			DebugHelper::Print("Failed To Create ScreenLayerWidget");
			return;
		}

		ScreenLayerWidget->AddToViewport();
	}
}

void UUISubsystem::PushContentToLayer(const EUIType UIType, UUserWidget* Content)
{
	if (!IsValid(Content)) return;
	if (!Layers.Contains(UIType)) return;

	Layers[UIType]->PushContentToLayer(Content);
}

void UUISubsystem::ClearLayer(const EUIType UIType)
{
	if (Layers.Contains(UIType))
	{
		Layers[UIType]->ClearLayer();
	}
}
