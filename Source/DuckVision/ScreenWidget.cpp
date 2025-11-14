// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidget.h"
#include "Components/Overlay.h"

void UScreenWidget::RegisterLayer(UUserWidget* Layer)
{
	if (!IsValid(Overlay)) return;
	if (!IsValid(Layer)) return;

	Overlay->AddChild(Layer);
}
