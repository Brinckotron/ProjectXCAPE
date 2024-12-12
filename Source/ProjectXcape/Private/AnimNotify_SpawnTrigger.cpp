// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SpawnTrigger.h"

void UAnimNotify_SpawnTrigger::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast();
	Super::Notify(MeshComp, Animation, EventReference);
}
