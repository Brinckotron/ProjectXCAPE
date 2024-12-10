// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierBowl.h"

#include "EditorMetadataOverrides.h"
#include "Torch.h"
#include "Algo/RandomShuffle.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"

// Sets default values
ABrazierBowl::ABrazierBowl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Brazier = CreateDefaultSubobject<UStaticMeshComponent>("Brazier");
	RootComponent = Brazier;
	FireEffect = CreateDefaultSubobject<UNiagaraComponent>("FireEffect");
	FireEffect->AttachToComponent(Brazier, FAttachmentTransformRules::KeepRelativeTransform);
	LightSource = CreateDefaultSubobject<UPointLightComponent>("LightSource");
	LightSource->AttachToComponent(FireEffect, FAttachmentTransformRules::KeepRelativeTransform);
	IsLit = false;
}

// Called when the game starts or when spawned
void ABrazierBowl::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AProjectXcapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	LightSource->SetLightFunctionMaterial(LightFunctions[FMath::RandRange(0,4)]);
	
	if(FireEffect && IsLit)
	{
		LightFire();
	}
	else
	{
		LightSource->SetVisibility(false);
	}
	
}

// Called every frame
void ABrazierBowl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrazierBowl::Interact()
{
	auto Torch = Cast<ATorch>(Player->Inventory[Player->CurrentItemIndex]);
	if (Torch)
	{
		if (IsLit && !Torch->IsLit)
		{
			Torch->LightTorch();
		}
		else if (!IsLit && Torch->IsLit)
		{
			LightFire();
		}
	}
}

FString ABrazierBowl::ShowInteractText()
{
	FString string = "";

	auto Torch = Cast<ATorch>(Player->Inventory[Player->CurrentItemIndex]);
	if (Torch)
	{
		if (IsLit && !Torch->IsLit)
		{
			string = "R to Light Torch";
		}
		else if (!IsLit && Torch->IsLit)
		{
			string = "R to Light Brazier";
		}
	}
	return string;
}

FString ABrazierBowl::ShowName()
{
	return "Brazier";
}

void ABrazierBowl::LightFire()
{
		FireEffect->ActivateSystem();
		LightSource->SetVisibility(true);
		IsLit = true;
}

