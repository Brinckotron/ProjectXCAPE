// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierBowl.h"

// Sets default values
ABrazierBowl::ABrazierBowl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Brazier = CreateDefaultSubobject<UStaticMeshComponent>("Brazier");
	RootComponent = Brazier;
	FireEffect = CreateDefaultSubobject<UNiagaraComponent>("FireEffect");
	FireEffect->AttachToComponent(Brazier, FAttachmentTransformRules::KeepRelativeTransform);
	//LightSource = CreateDefaultSubobject<UPointLightComponent>("LightSource");
	//LightSource->AttachToComponent(FireEffect, FAttachmentTransformRules::KeepRelativeTransform);
	IsLit = false;

}

// Called when the game starts or when spawned
void ABrazierBowl::BeginPlay()
{
	Super::BeginPlay();
	if(FireEffect && IsLit)
	{
		LightFire();
	}
	else
	{
		//LightSource->SetVisibility(false);
	}
	
}

// Called every frame
void ABrazierBowl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrazierBowl::Interact(AActor* Interactor)
{
	LightFire();
}

void ABrazierBowl::LightFire()
{
	if (!IsLit && FireEffect)
	{
		FireEffect->ActivateSystem();
		//LightSource->SetVisibility(true);
		IsLit = true;
	}
}

