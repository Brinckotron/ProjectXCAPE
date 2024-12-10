// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Anubis.h"

#include "Anubis.h"

AAIC_Anubis::AAIC_Anubis(FObjectInitializer const& ObjectInitializer)
{
}

void AAIC_Anubis::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(AAnubis* const anubis = Cast<AAnubis>(InPawn))
	{
		if (UBehaviorTree* const tree = anubis->GetBehaviourTree())
		{
			UBlackboardComponent* bb;
			UseBlackboard(tree->BlackboardAsset, bb);
			Blackboard = bb;
			RunBehaviorTree(tree);
		}
	}
}
