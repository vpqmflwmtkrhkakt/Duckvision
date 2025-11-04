// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

AWeapon::AWeapon()
{
	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	check(RootComp);

	SetRootComponent(RootComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	check(Mesh);

	Mesh->SetupAttachment(RootComp);

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
}

