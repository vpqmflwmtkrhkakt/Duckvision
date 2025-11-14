// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UILayer.generated.h"

class UBorder;
UCLASS()
class DUCKVISION_API UUILayer : public UUserWidget
{
	GENERATED_BODY()
public:
	void ClearLayer();
	void PopLayer();
	void ShowTopWidget();
	void CollapseTopWidget();
	UUserWidget* GetTopWidget();
	UUserWidget* PushContentToLayer(UUserWidget* Content);
private:
	void ClearBorder();

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UBorder* BorderUI;
	TArray<UUserWidget*> Widgets;
};
