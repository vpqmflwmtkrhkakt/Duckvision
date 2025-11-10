// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupWidget.h"
#include "DebugHelper.h"
#include "Components/WidgetComponent.h"
#include "Animation/WidgetAnimation.h"

bool UPopupWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	EndDelegate.BindDynamic(this, &ThisClass::OnPopupAnimationFinished);

	return true;
}

void UPopupWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
}

void UPopupWidget::ShowUI()
{
	if (IsValid(Popup))
	{
		UnbindAllFromAnimationFinished(Popup);

		PlayAnimation(Popup, 0.f, 1, EUMGSequencePlayMode::Forward);
	}
}

void UPopupWidget::HideUI()
{
	if (IsValid(Popup))
	{
		PlayAnimation(Popup, 0.f, 1, EUMGSequencePlayMode::Reverse);

		BindToAnimationFinished(Popup, EndDelegate);
	}
}

void UPopupWidget::OnPopupAnimationFinished()
{
	if (UWidgetComponent* WidgetComponent = Cast<UWidgetComponent>(GetOuter()))
	{
		WidgetComponent->SetVisibility(false);
	}

	UnbindAllFromAnimationFinished(Popup);
}
