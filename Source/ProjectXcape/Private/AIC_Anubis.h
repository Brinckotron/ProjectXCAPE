// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Anubis.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIC_Anubis.generated.h"

/**
 * AI Controller for Anubis enemy with dynamic perception system
 */
UCLASS()
class AAIC_Anubis : public AAIController
{
	GENERATED_BODY()

public:
	explicit AAIC_Anubis(FObjectInitializer const& ObjectInitializer);
	void Activate();
	AActor* FindWaypoint();
	FVector FindPlayer();
	void Attack();
	UPROPERTY(EditAnywhere)
	bool IsActivated;
	AAnubis* Anubis;
	// Sight radius values for normal and Ankh-protected states
	float sightRadius;
	float reducedSightRadius;
	UPROPERTY(EditAnywhere)
	bool IgnorePlayer;
	

protected:
	
	virtual void OnPossess(APawn* InPawn) override;
	void AttackDoneNotify();


private:
	class UAISenseConfig_Sight* SightConfig;
	
	void SetupPerceptionSystem();
	// Dynamic perception adjustment based on player's Ankh status
	UFUNCTION()
	void UpdatePerceptionSystem(bool isAnkhEquipped);

	// AI perception callback for player detection
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

protected:
	virtual void BeginPlay() override;
};
