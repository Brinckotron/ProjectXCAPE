// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneTabletSlot.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"

// Sets default values
AStoneTabletSlot::AStoneTabletSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentTablet = nullptr;

	Slot = CreateDefaultSubobject<UStaticMeshComponent>("Slot");
	RootComponent = Slot;

	TabletSnapPoint = CreateDefaultSubobject<USceneComponent>("TabletSnapPoint");
	TabletSnapPoint->AttachToComponent(Slot, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AStoneTabletSlot::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AProjectXcapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

}

// Called every frame
void AStoneTabletSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoneTabletSlot::Interact()
{
	auto Tablet = Cast<AStoneTablet>(Player->Inventory[Player->CurrentItemIndex]);
	if (Tablet)
	{
		Player->PlaceItem(TabletSnapPoint, true);
		CurrentTablet = Tablet;
		OnSlotUpdated.Broadcast();
	}
}

FString AStoneTabletSlot::ShowInteractText()
{
	FString string;
	auto Tablet = Cast<AStoneTablet>(Player->Inventory[Player->CurrentItemIndex]);
	if (Tablet)
	{
		string = "Click to place " + Tablet->ItemName();
	}
	return string;
}

FString AStoneTabletSlot::ShowName()
{
	return "Tablet Slot";
}


bool AStoneTabletSlot::IsCorrectTablet() const
{
	return CurrentTablet && CurrentTablet->TabletID == SlotID;
}

FString AStoneTabletSlot::InspectLore()
{
	return "";
}

