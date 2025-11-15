// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidget.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void UScreenWidget::RegisterLayer(UUserWidget* Layer)
{
    if (!IsValid(Overlay) || !IsValid(Layer))
        return;

    UOverlaySlot* AddedSlot = Overlay->AddChildToOverlay(Layer);

    AddedSlot->SetHorizontalAlignment(HAlign_Fill);
    AddedSlot->SetVerticalAlignment(VAlign_Fill);
    AddedSlot->SetPadding(FMargin(0));

    Layer->SetVisibility(ESlateVisibility::Visible);
}

