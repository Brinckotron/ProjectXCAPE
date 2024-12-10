// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivateAnubisTrigger.h"

#include "AIC_Anubis.h"
#include "Kismet/GameplayStatics.h"

AActivateAnubisTrigger::AActivateAnubisTrigger(FObjectInitializer const& ObjectInitializer)
{
	 
}

void AActivateAnubisTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void AActivateAnubisTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (Cast<AProjectXcapeCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger!"));
		if (auto* const anubisAI = Cast<AAIC_Anubis>(Anubis->GetController()))
		{
			anubisAI->Activate();
		}
	}
}
