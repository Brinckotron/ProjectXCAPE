// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoneTabletSlot.h"
#include "GameFramework/Actor.h"
#include "PuzzleDoor.generated.h"

UCLASS()
class APuzzleDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<AStoneTabletSlot*> Slots;

	// Checks if the puzzle is solved
	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void CheckPuzzleSolved();

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void OpenDoor();


private:
	UFUNCTION()
	void OnSlotUpdated();
};
