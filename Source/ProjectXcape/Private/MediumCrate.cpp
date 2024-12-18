// Fill out your copyright notice in the Description page of Project Settings.


#include "MediumCrate.h"

#include "PlayerWidget.h"
#include "PryingTool.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMediumCrate::AMediumCrate()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	OpenLidPoint = CreateDefaultSubobject<USceneComponent>("OpenLidPoint");
	OpenLidPoint->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Bottom = CreateDefaultSubobject<UStaticMeshComponent>("Bottom");
	Bottom->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Lid = CreateDefaultSubobject<UStaticMeshComponent>("Lid");
	Lid->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	for (int i = 0; i < 4; i++)
	{
		FString ComponentName = FString::Printf(TEXT("Side_%d"), i);
		UStaticMeshComponent* SideComp = CreateDefaultSubobject<UStaticMeshComponent>(*ComponentName);
		SideComp->SetupAttachment(Root);
		Sides.Add(SideComp);
	}
	
	
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMediumCrate::BeginPlay()
{
	Player = Cast<AProjectXcapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (IsOpen)
	{
		OpenLid();
	}
	Super::BeginPlay();
}

// Called every frame
void AMediumCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AMediumCrate::Interact()
{
	if (!IsOpen)
	{
		if (auto* const bar = Cast<APryingTool>(Player->Inventory[Player->CurrentItemIndex]))
		{
			OpenLid();
		}
		else
		{
			Player->PlayerWidget->ShowLore(InspectLore(),3.f);
		}
	}
}

FString AMediumCrate::ShowInteractText()
{
	if (!IsOpen)
	{
		if (auto* const bar = Cast<APryingTool>(Player->Inventory[Player->CurrentItemIndex]))
		{
			return "Open";
		}
		
		return "Examine";
	}
		return "";
	
}

FString AMediumCrate::ShowName()
{
	return "Crate";
}

void AMediumCrate::OpenLid()
{
	IsOpen = true;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;  
	
	FVector openPos = OpenLidPoint->GetRelativeLocation();
	FRotator openRot = OpenLidPoint->GetRelativeRotation();
	
	UKismetSystemLibrary::MoveComponentTo(Lid, openPos, openRot, false, true, 0.1f, false, EMoveComponentAction::Move, LatentInfo);
}

FString AMediumCrate::InspectLore()
{
	return "Perhaps I could open this with the right tool.";
}


