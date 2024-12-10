// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTAsk_Attack.h"

#include "AIC_Anubis.h"
#include "NavigationSystem.h"

UBTTAsk_Attack::UBTTAsk_Attack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTAsk_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AAIC_Anubis>(OwnerComp.GetAIOwner()))
	{
		cont->Attack();
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
