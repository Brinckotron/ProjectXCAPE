// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "GameFramework/Actor.h"
#include "PryingTool.generated.h"

UCLASS()
class APryingTool : public AActor, public IInventoryItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APryingTool();

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Bar;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Tip;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FString ItemName() override;
	virtual FString LoreText() override;
};