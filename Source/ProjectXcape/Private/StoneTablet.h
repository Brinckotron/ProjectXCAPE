// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "StoneTablet.generated.h"

UCLASS()
class AStoneTablet : public AActor, public IInventoryItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoneTablet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	UStaticMeshComponent* Tablet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	int32 TabletID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TabletName;

	virtual FString ItemName() override;
	virtual FString LoreText() override;
};
