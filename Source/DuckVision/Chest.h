// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Chest.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UUserWidget;
UCLASS()
class DUCKVISION_API AChest : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);


	UFUNCTION()
    void OnEndOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex
    );

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, Category = TriggerSphere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* TriggerSphere;


	// IInteractableInterface을(를) 통해 상속됨
	void Interact(AActor* Caller) override;


private:
	TSubclassOf<UUserWidget> ChestUIClass;
	UUserWidget* ChestUI;

};
