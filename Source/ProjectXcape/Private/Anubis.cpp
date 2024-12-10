// Fill out your copyright notice in the Description page of Project Settings.


#include "Anubis.h"

#include "AnubisWaypoint.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
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

