// Fill out your copyright notice in the Description page of Project Settings.


#include "StatuetteBase.h"

#include "Statuette.h"
#include "Kismet/GameplayStatics.h"
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
	Player = Cast<AProjectXcapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
}

void AStatuetteBase::OpenDoor()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	FTransform OriginalTransform = Door->GetTransform();
	UKismetSystemLibrary::MoveComponentTo(Door->GetRootComponent(), OriginalTransform.GetLocation() + FVector(0.f, 0.f, 480.f), OriginalTransform.Rotator(), true, true, 10.f, true, EMoveComponentAction::Move, LatentInfo);
}

// Called every frame
void AStatuetteBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStatuetteBase::Interact()
{
	auto Statuette = Cast<AStatuette>(Player->Inventory[Player->CurrentItemIndex]);
	if (Statuette)
	{
		Player->PlaceItem(SlotPoint, false);
		OpenDoor();
		Player->ShakeCamera();
	}
	
}

FString AStatuetteBase::ShowInteractText()
{
	FString string;
		auto Statuette = Cast<AStatuette>(Player->Inventory[Player->CurrentItemIndex]);
		if (Statuette)
		{
			string = "Click to place Statuette";
		}
	return string;
}

FString AStatuetteBase::ShowName()
{
	return "Statuette Base";
}

FString AStatuetteBase::InspectLore()
{
	return "";
}

