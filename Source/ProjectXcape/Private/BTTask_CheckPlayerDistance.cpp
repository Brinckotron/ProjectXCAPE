// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckPlayerDistance.h"

#include "AIC_Anubis.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckPlayerDistance::UBTTask_CheckPlayerDistance(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Check Player Distance";
}

EBTNodeResult::Type UBTTask_CheckPlayerDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AAIC_Anubis>(OwnerComp.GetAIOwner()))
	{
		int distance = FVector::Dist(cont->Anubis->GetActorLocation(), cont->FindPlayer());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), distance <= 200.f );
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
