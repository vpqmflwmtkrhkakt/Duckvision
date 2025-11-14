// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenWidget.generated.h"

class UOverlay;
UCLASS()
class DUCKVISION_API UScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void RegisterLayer(UUserWidget* Layer);

private:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay;
};
