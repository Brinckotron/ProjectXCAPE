// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTAsk_Attack.generated.h"

/**
 * 
 */
UCLASS()
class UBTTAsk_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTAsk_Attack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
