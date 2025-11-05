// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class DUCKVISION_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	void SetupWeapon(AActor* IncomingOwner);
	FTransform GetSocketTransform() const;
	const FVector& GetJointTargetLocation() const;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void Fire();


private:
	UPROPERTY(EditDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	float FireRate;
	UPROPERTY(EditDefaultsOnly, Category = Ammo, meta = (AllowPrivateAccess = "true"))
	int32 MaxRound;
	int32 CurrentRound = 0;

	UPROPERTY(EditDefaultsOnly, Category = JoinTarget, meta = (AllowPrivateAccess = "true"))
	FVector JoinTargetLocation;

	TSubclassOf<AActor> BulletClass;

	AActor* Bullet;
};
