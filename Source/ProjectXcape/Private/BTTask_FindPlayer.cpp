// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayer.h"

#include "AIC_Anubis.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPlayer::UBTTask_FindPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Player";
}

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AAIC_Anubis>(OwnerComp.GetAIOwner()))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), cont->FindPlayer());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	
	
	return EBTNodeResult::Failed;
}
