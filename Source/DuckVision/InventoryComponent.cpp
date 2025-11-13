// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "DebugHelper.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
void UInventoryComponent::ToggleInventory()
{
	DebugHelper::Print("Toggle Inventory");
}



