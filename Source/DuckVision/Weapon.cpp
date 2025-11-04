// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

AWeapon::AWeapon()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	check(Root);

	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	check(Mesh);

	Mesh->SetupAttachment(Root);
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

