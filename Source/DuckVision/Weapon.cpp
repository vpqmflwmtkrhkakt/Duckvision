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

	ConstructorHelpers::FClassFinder<AActor> BulletClassFinder(TEXT("/Game/DuckVision/Blueprints/BP_Bullet"));

	if (BulletClassFinder.Succeeded())
	{
		BulletClass = BulletClassFinder.Class;
	}
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

FTransform AWeapon::GetSocketTransform() const
{
	FName SocketName = TEXT("LHIK");
	return Mesh->GetSocketTransform(SocketName);
}

const FVector& AWeapon::GetJointTargetLocation() const
{
	return JoinTargetLocation;
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
	if (BulletClass)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = GetActorRotation();
		GetWorld()->SpawnActor(BulletClass, &Location, &Rotation);
	}
}

