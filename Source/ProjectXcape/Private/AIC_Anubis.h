// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_Anubis.generated.h"

/**
 * 
 */
UCLASS()
class AAIC_Anubis : public AAIController
{
	GENERATED_BODY()

public:
	explicit AAIC_Anubis(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
