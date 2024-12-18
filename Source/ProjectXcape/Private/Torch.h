// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "NiagaraComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "Torch.generated.h"

UCLASS()
class ATorch : public AActor, public IInventoryItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorch();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TorchHandle;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TorchTip;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* TorchFlame;
	UPROPERTY(EditAnywhere)
	UPointLightComponent* TorchLight;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FString ItemName() override;
	bool IsLit;

	void LightTorch();
	void ExtinguishTorch();
	virtual FString LoreText() override;
};
