// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "Components/SphereComponent.h"
#include "DebugHelper.h"
#include "DuckVisionCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PopupWidget.h"
#include "UISubsystem.h"

AChest::AChest()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(Root);

	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(Mesh);

	Mesh->SetupAttachment(Root);

	UIWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("UIWidget"));
	check(UIWidgetComponent);

	UIWidgetComponent->SetupAttachment(Root);
	UIWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	UIWidgetComponent->SetTwoSided(true);
	UIWidgetComponent->SetBlendMode(EWidgetBlendMode::Transparent);
	UIWidgetComponent->SetDrawAtDesiredSize(true);
	UIWidgetComponent->SetDrawSize(FVector2D(400, 400));
	UIWidgetComponent->SetPivot(FVector2D(0.5f, 0.5f));

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	check(TriggerSphere);

	TriggerSphere->SetupAttachment(Root);

	PrimaryActorTick.bCanEverTick = true;
}

void AChest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MakeInteractUIFaceCam();
}

void AChest::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);

	if (IsValid(UIWidgetComponent))
	{
		UIWidgetComponent->SetVisibility(false);
	}

}

void AChest::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADuckVisionCharacter* DuckCharacter = Cast<ADuckVisionCharacter>(OtherActor);

	if (IsValid(DuckCharacter))
	{
		DuckCharacter->SetInteractableObject(this);

		// 머티리얼 오버레이 
		if (Mesh && IsValid(OutlineMaterial))
		{
			Mesh->SetOverlayMaterial(OutlineMaterial);
		}

		// Interaction UI
		if (IsValid(UIWidgetComponent))
		{
			UIWidgetComponent->SetVisibility(true);

			UPopupWidget* Widget = Cast<UPopupWidget>(UIWidgetComponent->GetWidget());

			if (IsValid(Widget))
			{
				Widget->ShowUI();
			}
		}
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

		UWorld* World = GetWorld();

		if (!IsValid(World)) return;

		UGameInstance* CurrentGameInstance = World->GetGameInstance();

		if (!IsValid(CurrentGameInstance)) return;

		UUISubsystem* SubSystem = CurrentGameInstance->GetSubsystem<UUISubsystem>();

		if (SubSystem)
		{
			SubSystem->CloseToggleUI(ELayerType::IngameMenu, UITypeEnum::SearchResult);
		}

		if (IsValid(UIWidgetComponent))
		{
			UPopupWidget* Widget = Cast<UPopupWidget>(UIWidgetComponent->GetWidget());

			if (IsValid(Widget))
			{
				Widget->HideUI();
			}
		}


		if (Mesh && IsValid(OutlineMaterial))
		{
			Mesh->SetOverlayMaterial(nullptr);
		}
	}
}

void AChest::Interact(AActor* Caller)
{
	ToggleChestUI();
}

void AChest::MakeInteractUIFaceCam()
{
	if (IsValid(UIWidgetComponent) && UIWidgetComponent->IsVisible())
	{
		APlayerCameraManager* Cam = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		if (!Cam) return;

		FVector CameraLoc = Cam->GetCameraLocation();
		FVector ToCam = CameraLoc - UIWidgetComponent->GetComponentLocation();
		FRotator LookAt = FRotationMatrix::MakeFromX(ToCam).Rotator();
		UIWidgetComponent->SetWorldRotation(LookAt);
	}
}

void AChest::ToggleChestUI()
{
	UWorld* World = GetWorld();

	if (!IsValid(World)) return;

	UGameInstance* CurrentGameInstance = World->GetGameInstance();

	if (!IsValid(CurrentGameInstance)) return;

	UUISubsystem* SubSystem = CurrentGameInstance->GetSubsystem<UUISubsystem>();

	if (SubSystem)
	{
		SubSystem->ToggleUI(ELayerType::IngameMenu, UITypeEnum::SearchResult);
	}
}


