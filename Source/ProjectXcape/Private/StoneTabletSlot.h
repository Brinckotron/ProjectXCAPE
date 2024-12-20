// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactible.h"
#include "StoneTablet.h"
#include "GameFramework/Actor.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"
#include "StoneTabletSlot.generated.h"

UCLASS()
class AStoneTabletSlot : public AActor, public IInteractible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoneTabletSlot();
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

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Slot;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* TabletSnapPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	int32 SlotID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	AStoneTablet* CurrentTablet;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlotUpdated);
	UPROPERTY(BlueprintAssignable, Category = "Puzzle")
	FOnSlotUpdated OnSlotUpdated;
	
	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	bool IsCorrectTablet() const;
	virtual FString InspectLore() override;
};
