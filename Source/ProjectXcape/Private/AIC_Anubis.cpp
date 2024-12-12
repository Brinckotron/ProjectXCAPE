// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Anubis.h"

#include "Anubis.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

AAIC_Anubis::AAIC_Anubis(FObjectInitializer const& ObjectInitializer)
{
	IsActivated = false;
	sightRadius = 1500;
	reducedSightRadius = 750;
	SetupPerceptionSystem();
}

void AAIC_Anubis::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Anubis = Cast<AAnubis>(InPawn);
}

void AAIC_Anubis::AttackDoneNotify()
{
	GetBlackboardComponent()->SetValueAsBool("IsAttacking", false);
}

void AAIC_Anubis::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component"));
		SightConfig->SightRadius = sightRadius;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 100.f;
		SightConfig->PeripheralVisionAngleDegrees = 160.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 700.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_Anubis::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AAIC_Anubis::UpdatePerceptionSystem(bool isAnkhEquipped)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, isAnkhEquipped? TEXT("Equipped!"): TEXT("Unequipped!"), true);
	if(SightConfig)
	{
		SightConfig->SightRadius = isAnkhEquipped? reducedSightRadius: sightRadius;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 100.f;
		SightConfig->PeripheralVisionAngleDegrees = isAnkhEquipped?100.f : 160.f;
		SightConfig->AutoSuccessRangeFromLastSeenLocation = isAnkhEquipped?400.f : 700.f;
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AAIC_Anubis::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const ch = Cast<AProjectXcapeCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}

void AAIC_Anubis::BeginPlay()
{
	AProjectXcapeCharacter* PlayerCharacter = Cast<AProjectXcapeCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->OnAnkhUpdated.AddDynamic(this, &AAIC_Anubis::UpdatePerceptionSystem);
	}
	Super::BeginPlay();
}

void AAIC_Anubis::Activate()
{
	if (Anubis)
	{
		if (UBehaviorTree* const tree = Anubis->GetBehaviourTree())
		{
			UBlackboardComponent* bb;
			UseBlackboard(tree->BlackboardAsset, bb);
			Blackboard = bb;
			RunBehaviorTree(tree);
			IsActivated = true;
		}
	}
}

AActor* AAIC_Anubis::FindWaypoint()
{
	int waypointIndex = Anubis->CurrentWaypointIndex;
	if (Anubis->Waypoints.Num() > 0)
	{
		Anubis->CurrentWaypointIndex = (Anubis->CurrentWaypointIndex + 1) % Anubis->Waypoints.Num();
	}
	return Anubis->Waypoints[waypointIndex];
}

FVector AAIC_Anubis::FindPlayer()
{
	return Anubis->Player->GetActorLocation();
}

void AAIC_Anubis::Attack()
{
	Anubis->PlayAttackMontage();
	GetBlackboardComponent()->SetValueAsBool("IsAttacking", true);
}
