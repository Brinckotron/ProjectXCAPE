// Fill out your copyright notice in the Description page of Project Settings.


#include "Anubis.h"

#include "AnimNotify_DespawnTrigger.h"
#include "AnimNotify_SpawnTrigger.h"
#include "AnubisWaypoint.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAnubis::AAnubis()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LeftLight = CreateDefaultSubobject<USpotLightComponent>("LeftLight");
	LeftLight->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	RightLight = CreateDefaultSubobject<USpotLightComponent>("RightLight");
	RightLight->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	HitBoxOrigin = CreateDefaultSubobject<USceneComponent>("HitBoxOrigin");
	HitBoxOrigin->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	CurrentWaypointIndex = 0;
}

UBehaviorTree* AAnubis::GetBehaviourTree() const
{
	return Tree;
}

void AAnubis::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(AttackAnimMontage, 1.0f);
	}
}

// Called when the game starts or when spawned
void AAnubis::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AProjectXcapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnubisWaypoint::StaticClass(), TempWaypoints);
	Waypoints = SortWaypoints(TempWaypoints);

	if (HitBox)
	{
		FAttachmentTransformRules const Rules{
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false};
		HitBox->AttachToComponent(HitBoxOrigin, Rules);
		HitBox->SetGenerateOverlapEvents(false);
		HitBox->OnComponentBeginOverlap.AddDynamic(this, &AAnubis::BeginOverlap);
	}
	RegisterNotifies();
	
}

void AAnubis::RegisterNotifies()
{
	if (AttackAnimMontage)
	{
		const auto NotifyEvents = AttackAnimMontage->Notifies;
		for (FAnimNotifyEvent EventNotify : NotifyEvents)
		{
			if (const auto SpawnTriggerNotify = Cast<UAnimNotify_SpawnTrigger>(EventNotify.Notify))
			{
				SpawnTriggerNotify->OnNotified.AddUObject(this,&AAnubis::NotifySpawnTrigger);
			}
			if (const auto DespawnTriggerNotify = Cast<UAnimNotify_DespawnTrigger>(EventNotify.Notify))
			{
				DespawnTriggerNotify->OnNotified.AddUObject(this,&AAnubis::NotifyDespawnTrigger);
			}
		}
	}
}

void AAnubis::NotifySpawnTrigger()
{
	HitBox->SetGenerateOverlapEvents(true);
}

void AAnubis::NotifyDespawnTrigger()
{
	HitBox->SetGenerateOverlapEvents(false);
}

TArray<AAnubisWaypoint*> AAnubis::SortWaypoints(TArray<AActor*> wplist)
{
	TArray<AAnubisWaypoint*> sortedList;
	int currentwp = 0;
	int numberOfWP = TempWaypoints.Num();

	for (int i=0; i < numberOfWP; i++)
	{
		for (AActor* TempWaypoint : TempWaypoints)
		{
			if (auto* const wp = Cast<AAnubisWaypoint>(TempWaypoint))
			{
				
				if (wp->OrderNumber == currentwp)
				{
					sortedList.Add(Cast<AAnubisWaypoint>(TempWaypoint));
					currentwp++;
					break;
				}
			}
		
			
		}
		
	}
	

	return sortedList;
}

// Called every frame
void AAnubis::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAnubis::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAnubis::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (HitBox && OverlappedComponent == HitBox && OtherActor == Player)
	{
		HitBox->SetGenerateOverlapEvents(false);
	}
}

