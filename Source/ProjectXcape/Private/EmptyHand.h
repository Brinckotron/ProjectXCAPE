// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "GameFramework/Actor.h"
#include "EmptyHand.generated.h"

UCLASS()
class AEmptyHand : public AActor, public IInventoryItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEmptyHand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FString ItemName() override;

};
