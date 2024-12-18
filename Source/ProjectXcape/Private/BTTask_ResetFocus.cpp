// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ResetFocus.h"

#include "AIC_Anubis.h"

UBTTask_ResetFocus::UBTTask_ResetFocus(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Reset Focus";
}

EBTNodeResult::Type UBTTask_ResetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AAIC_Anubis>(OwnerComp.GetAIOwner()))
	{
		cont->ClearFocus(EAIFocusPriority::Gameplay);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
