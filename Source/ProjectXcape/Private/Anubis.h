// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnubisWaypoint.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"
#include "Anubis.generated.h"

UCLASS()
class AAnubis : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnubis();
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* AnubisMesh;
	UPROPERTY(EditAnywhere)
	USpotLightComponent* LeftLight;
	UPROPERTY(EditAnywhere)
	USpotLightComponent* RightLight;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> Waypoints;
	UPROPERTY(EditAnywhere)
	int CurrentWaypointIndex;
	AProjectXcapeCharacter* Player;

	//AI
	UBehaviorTree* GetBehaviourTree() const;
	
	
	//Animation
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> WalkAnimMontage;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//AI
	UPROPERTY(EditAnywhere)
	UBehaviorTree* Tree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
