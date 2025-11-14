// Fill out your copyright notice in the Description page of Project Settings.


#include "UILayer.h"
#include "Components/Border.h"

void UUILayer::ClearLayer()
{
	Border->ClearChildren();

	for (auto& Widget : Widgets)
	{
		Widget->RemoveFromParent();
	}

	Widgets.Empty();
}

UUserWidget* UUILayer::GetTopWidget()
{
	return Widgets.IsEmpty() ? nullptr : Widgets.Top();
}

void UUILayer::PopLayer()
{
	if (!Widgets.IsEmpty())
	{
		UUserWidget* TopWidget = Widgets.Top();

		TopWidget->SetVisibility(ESlateVisibility::Visible);
		Border->AddChild(TopWidget);
	}
}

void UUILayer::ShowTopWidget()
{
	if (Widgets.IsEmpty()) return;

	Widgets.Top()->SetVisibility(ESlateVisibility::Visible);
}

void UUILayer::CollapseTopWidget()
{
	if (Widgets.IsEmpty()) return;

	Widgets.Top()->SetVisibility(ESlateVisibility::Collapsed);
}

void UUILayer::ClearBorder()
{
	if (Widgets.IsEmpty()) return;

	UUserWidget* TopWidget = Widgets.Top();

	TopWidget->SetVisibility(ESlateVisibility::Collapsed);

	Border->ClearChildren();
}
