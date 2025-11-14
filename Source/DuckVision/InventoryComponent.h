// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InvenSlotData.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, int32, FInvenSlotData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUCKVISION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FOnItemAdded OnItemAdded;
	void AddItem(FItemData& ItemData);
		
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items", meta = (AllowPriateAccess = "true"))
	TArray<FInvenSlotData> ItemDatas;
};
