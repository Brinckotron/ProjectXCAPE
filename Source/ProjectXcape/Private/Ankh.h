// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "Ankh.generated.h"

UCLASS()
class AAnkh : public AActor, public IInventoryItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnkh();
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Ankh;
	UPROPERTY(EditAnywhere)
	UPointLightComponent* LightSource;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FString ItemName() override;
};
