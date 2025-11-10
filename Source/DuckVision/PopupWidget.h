// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupWidget.generated.h"

class UWidgetAnimation;

UCLASS()
class DUCKVISION_API UPopupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	void SetVisibility(ESlateVisibility InVisibility) override;

	UFUNCTION(BlueprintCallable)
	void ShowUI();

	
	UFUNCTION(BlueprintCallable)
	void HideUI();

	UFUNCTION()
	void OnPopupAnimationFinished();
	
private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Popup;
	FWidgetAnimationDynamicEvent EndDelegate;
};

