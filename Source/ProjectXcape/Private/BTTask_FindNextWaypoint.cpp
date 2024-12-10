// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNextWaypoint.h"

#include "AIC_Anubis.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindNextWaypoint::UBTTask_FindNextWaypoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Next Waypoint";
}

EBTNodeResult::Type UBTTask_FindNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AAIC_Anubis>(OwnerComp.GetAIOwner()))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), cont->FindWaypoint()->GetActorLocation());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	
	
	return EBTNodeResult::Failed;
	
}
