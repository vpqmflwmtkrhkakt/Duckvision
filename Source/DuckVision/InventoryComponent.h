// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUCKVISION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void ToggleInventory();
		
protected:
	virtual void BeginPlay() override;

		
};
