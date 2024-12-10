// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/PointLightComponent.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"
#include "ProjectXcape/Public/Interactible.h"
#include "BrazierBowl.generated.h"





UCLASS()
class ABrazierBowl : public AActor, public IInteractible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrazierBowl();
	UPROPERTY(EditAnywhere, Category = "Brazier")
	UStaticMeshComponent* Brazier;
	UPROPERTY(EditAnywhere, Category = "Brazier")
	UNiagaraComponent* FireEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent* LightSource;
	UPROPERTY(EditAnywhere)
	bool IsLit;
	AProjectXcapeCharacter* Player;
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> LightFunctions;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	virtual FString ShowInteractText() override;

	virtual FString ShowName() override;

	void LightFire();
	
	
};
