// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneTabletSlot.h"

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
	
}

// Called every frame
void AStoneTabletSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoneTabletSlot::PlaceTablet(AStoneTablet* Tablet)
{
	CurrentTablet = Tablet;
	OnSlotUpdated.Broadcast();
}

bool AStoneTabletSlot::IsCorrectTablet() const
{
	return CurrentTablet && CurrentTablet->TabletID == SlotID;
}

