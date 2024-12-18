// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTAsk_Activate.h"

#include "AIC_Anubis.h"

UBTTAsk_Activate::UBTTAsk_Activate(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Activate";
}

EBTNodeResult::Type UBTTAsk_Activate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AAIC_Anubis>(OwnerComp.GetAIOwner()))
	{
		cont->Anubis->PlayActivateMontage();
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}