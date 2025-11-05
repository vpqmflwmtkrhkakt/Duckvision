// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "Components/SphereComponent.h"
#include "DebugHelper.h"
#include "DuckVisionCharacter.h"

AChest::AChest()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(Root);

	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(Mesh);

	Mesh->SetupAttachment(Root);


	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	check(TriggerSphere);

	TriggerSphere->SetupAttachment(Root);
}

void AChest::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void AChest::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADuckVisionCharacter* DuckCharacter = Cast<ADuckVisionCharacter>(OtherActor);

	if (IsValid(DuckCharacter))
	{
		DuckCharacter->SetInteractableObject(this);
	}
}

void AChest::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADuckVisionCharacter* DuckCharacter = Cast<ADuckVisionCharacter>(OtherActor);

	if (IsValid(DuckCharacter))
	{
		IInteractableInterface* Object = DuckCharacter->GetInteractableObject();

		if (Object == this)
		{
			DuckCharacter->SetInteractableObject(nullptr);
		}
	}
}

void AChest::Interact(AActor* Caller)
{
	DebugHelper::Print("Interact");
}


