// Fill out your copyright notice in the Description page of Project Settings.


#include "Ankh.h"

// Sets default values
AAnkh::AAnkh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	Ankh = CreateDefaultSubobject<UStaticMeshComponent>("Ankh");
	Ankh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	LightSource = CreateDefaultSubobject<UPointLightComponent>("LightSource");
	LightSource->AttachToComponent(Ankh, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AAnkh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnkh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AAnkh::ItemName()
{
	return "Ankh of Protection";
}

