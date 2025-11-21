// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverSystemComponent.h"
#include "DebugHelper.h"

UCoverSystemComponent::UCoverSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCoverSystemComponent::TakeCover()
{
	DebugHelper::Print("Taking Cover");
}


void UCoverSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCoverSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

