// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactible.h"
#include "GameFramework/Actor.h"
#include "StatuetteBase.generated.h"

UCLASS()
class AStatuetteBase : public AActor, public IInteractible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatuetteBase();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Base;
	UPROPERTY(EditAnywhere)
	USceneComponent* SlotPoint;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor) override;
	virtual FString ShowInteractText(AActor* Interactor) override;
	virtual FString ShowName() override;

};
