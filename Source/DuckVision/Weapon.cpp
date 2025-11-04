// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DuckVisionPlayerController.h"
#include "DebugHelper.h"

AWeapon::AWeapon()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	check(Root);

	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	check(Mesh);

	Mesh->SetupAttachment(Root);
}

void AWeapon::SetupWeapon(AActor* IncomingOwner)
{
	if (!IsValid(IncomingOwner)) return;

	SetOwner(IncomingOwner);

	ADuckVisionPlayerController* DuckVisionController = IncomingOwner->GetInstigatorController<ADuckVisionPlayerController>();

	if (IsValid(DuckVisionController))
	{
		DuckVisionController->OnFireWeapon.AddUObject(this, &ThisClass::Fire);
	}
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentRound = MaxRound;

}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Fire()
{
	DebugHelper::Print("Fire weapon");
}

