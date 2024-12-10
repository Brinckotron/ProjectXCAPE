// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNextWaypoint.h"

#include "AIC_Anubis.h"
#include "NavigationSystem.h"

UBTTask_FindNextWaypoint::UBTTask_FindNextWaypoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Next Waypoint";
}

EBTNodeResult::Type UBTTask_FindNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AAIC_Anubis>(OwnerComp.GetAIOwner()))
	{
		if (auto* const anubis = cont->GetPawn())
		{
			auto const Origin = anubis->GetActorLocation();

			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation loc;
				
			}
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
	
}
