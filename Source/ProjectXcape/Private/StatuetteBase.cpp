// Fill out your copyright notice in the Description page of Project Settings.


#include "StatuetteBase.h"

#include "Statuette.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"

// Sets default values
AStatuetteBase::AStatuetteBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Base = CreateDefaultSubobject<UStaticMeshComponent>("Base");
	RootComponent = Base;
	SlotPoint = CreateDefaultSubobject<UStaticMeshComponent>("SlotPoint");
	SlotPoint->AttachToComponent(Base, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AStatuetteBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStatuetteBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStatuetteBase::Interact(AActor* Interactor)
{
	auto Player = Cast<AProjectXcapeCharacter>(Interactor);
	auto Statuette = Cast<AStatuette>(Player->Inventory[Player->CurrentItemIndex]);
	if (Statuette)
	{
		Player->PlaceItem(SlotPoint);
	}
	
}

FString AStatuetteBase::ShowInteractText(AActor* Interactor)
{
	auto Player = Cast<AProjectXcapeCharacter>(Interactor);
	FString string;
		auto Statuette = Cast<AStatuette>(Player->Inventory[Player->CurrentItemIndex]);
		if (Statuette)
		{
			string = "R to place Statuette";
		}
	return string;
}

FString AStatuetteBase::ShowName()
{
	return "Statuette Base";
}

