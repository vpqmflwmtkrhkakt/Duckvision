// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UITypeEnum.h"
#include "UILayer.generated.h"

UCLASS()
class DUCKVISION_API UUILayer : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ClearLayer();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PopLayer();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowTopWidget();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CollapseTopWidget();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UUserWidget* GetTopWidget();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UUserWidget* PushContentToLayer(UUserWidget* Content);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UUserWidget* ToggleUI(UITypeEnum UIType);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseToggleUI(UITypeEnum UIType);

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ClearBorder();

};
