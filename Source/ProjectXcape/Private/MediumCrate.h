// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactible.h"
#include "GameFramework/Actor.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"
#include "MediumCrate.generated.h"

UCLASS()
class AMediumCrate : public AActor, public IInteractible
{
	GENERATED_BODY()
	
	
	
	
public:	
	// Sets default values for this actor's properties
	AMediumCrate();

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Bottom;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Lid;
	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> Sides;
	UPROPERTY(EditAnywhere)
	USceneComponent* OpenLidPoint;
	UPROPERTY(EditAnywhere)
	bool IsOpen;
	AProjectXcapeCharacter* Player;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;
	virtual FString ShowInteractText() override;
	virtual FString ShowName() override;
	void OpenLid();
	virtual FString InspectLore() override;
};
