// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTAsk_Activate.generated.h"

/**
 * 
 */
UCLASS()
class UBTTAsk_Activate : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTAsk_Activate(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
