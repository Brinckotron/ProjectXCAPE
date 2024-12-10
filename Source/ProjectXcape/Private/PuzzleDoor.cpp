// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleDoor.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APuzzleDoor::APuzzleDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	RootComponent = Door;

}

// Called when the game starts or when spawned
void APuzzleDoor::BeginPlay()
{
	Super::BeginPlay();

	for (AStoneTabletSlot* Slot : Slots)
	{
		if (Slot)
		{
			Slot->OnSlotUpdated.AddDynamic(this, &APuzzleDoor::OnSlotUpdated);
		}
	}
	
}

// Called every frame
void APuzzleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleDoor::CheckPuzzleSolved()
{
	for (AStoneTabletSlot* Slot : Slots)
	{
		if (!Slot->IsCorrectTablet())
		{
			return;
		}
	}

	OpenDoor();

}

void APuzzleDoor::OpenDoor()
{

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;  
	
	FVector doorPos = Door->GetRelativeLocation();
	FRotator doorRot = Door->GetRelativeRotation();
	
	FVector openPos = doorPos - FVector(0, 250,0);
	
	UKismetSystemLibrary::MoveComponentTo(Door, openPos, doorRot, true, true, 5.f, false, EMoveComponentAction::Move, LatentInfo);
	
}

void APuzzleDoor::OnSlotUpdated()
{
	CheckPuzzleSolved();
}

