// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anubis.h"
#include "Engine/TriggerBox.h"
#include "ActivateAnubisTrigger.generated.h"

/**
 * 
 */
UCLASS()
class AActivateAnubisTrigger : public ATriggerBox
{
	GENERATED_BODY()
public:
	explicit AActivateAnubisTrigger(FObjectInitializer const& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	AAnubis* Anubis;
	
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
