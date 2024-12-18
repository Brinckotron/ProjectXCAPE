// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"

#include "AIC_Anubis.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Chase Player";
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<AAIC_Anubis>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation =  OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		if (FVector::Dist(cont->Anubis->GetActorLocation(), cont->Anubis->Player->GetActorLocation()) > 200)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, PlayerLocation);
		}
		else
		{
			cont->StopMovement();
			cont->SetFocus(cont->Anubis->Player, EAIFocusPriority::Gameplay);
		}
			
		
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
