// Fill out your copyright notice in the Description page of Project Settings.


#include "GemYellow.h"

// Sets default values
AGemYellow::AGemYellow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	Gem = CreateDefaultSubobject<UStaticMeshComponent>("Gem");
	Gem->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AGemYellow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGemYellow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AGemYellow::ItemName()
{
	return Name;
}

FString AGemYellow::LoreText()
{
	return "A glowing " + Name + "... What could be it's purpose?";
}

