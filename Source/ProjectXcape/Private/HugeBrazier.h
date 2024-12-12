// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactible.h"
#include "NiagaraComponent.h"
#include "PuzzleDoor.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "HugeBrazier.generated.h"

class AProjectXcapeCharacter;

UCLASS()
class AHugeBrazier : public AActor, public IInteractible
{
public:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Brazier;
	UPROPERTY(EditAnywhere)
	UPointLightComponent* LightSource;
	UPROPERTY(EditAnywhere)
	AActor* PurpleDoor;
	UPROPERTY(EditAnywhere)
	AActor* GreenDoor;
	UPROPERTY(EditAnywhere)
	TArray<UNiagaraComponent*> Fires;
	bool IsLit;
	enum class EFlameColor : uint8
	{
		Red,
		Blue,
		Yellow,
		Green,
		Orange,
		Purple
	};
	EFlameColor currentColor;
	AProjectXcapeCharacter* Player;
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> LightFunctions;
	
	
	virtual void Interact() override;
	virtual FString ShowInteractText() override;
	virtual FString ShowName() override;
	void LightFire();
	void OpenDoor(AActor* Door);
	void Fire(int i);

private:
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AHugeBrazier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
