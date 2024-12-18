// Fill out your copyright notice in the Description page of Project Settings.


#include "Statuette.h"

// Sets default values
AStatuette::AStatuette()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PivotPoint = CreateDefaultSubobject<USceneComponent>("PivotPoint");
	RootComponent = PivotPoint;
	Statuette = CreateDefaultSubobject<UStaticMeshComponent>("Statuette");
	Statuette->AttachToComponent(PivotPoint, FAttachmentTransformRules::KeepRelativeTransform);
	Collar = CreateDefaultSubobject<UStaticMeshComponent>("Collar");
	Collar->AttachToComponent(Statuette, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AStatuette::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStatuette::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AStatuette::ItemName()
{
	return "Statuette of Anubis";
}

FString AStatuette::LoreText()
{
	return "This smaller idol seems tied to the guardian. Where might it belong?";
}

