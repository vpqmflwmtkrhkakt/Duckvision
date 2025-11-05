// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "Components/SphereComponent.h"
#include "DebugHelper.h"
#include "DuckVisionCharacter.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

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


	ConstructorHelpers::FClassFinder<UUserWidget> ChestUIClassFinder(TEXT("/Game/DuckVision/Blueprints/UI/WBP_ChestUI"));

	if (ChestUIClassFinder.Succeeded())
	{
		ChestUIClass = ChestUIClassFinder.Class;
	}
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

		if (ChestUI->IsInViewport())
		{
			ChestUI->RemoveFromParent();
		}
	}
}

void AChest::Interact(AActor* Caller)
{
	if (!IsValid(ChestUI))
	{
		if (!ChestUIClass) return;
		
		ADuckVisionCharacter* DuckVisionCharacter = Cast<ADuckVisionCharacter>(Caller);

		if (!IsValid(DuckVisionCharacter)) return;

		APlayerController* PC = Cast<APlayerController>(DuckVisionCharacter->GetController());

		if (!IsValid(PC)) return;

		ChestUI = CreateWidget(PC, ChestUIClass);

		if (!IsValid(ChestUI)) return;
	}

	ChestUI->AddToViewport();
}


