// Fill out your copyright notice in the Description page of Project Settings.


#include "PryingTool.h"

// Sets default values
APryingTool::APryingTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	Bar = CreateDefaultSubobject<UStaticMeshComponent>("Bar");
	Bar->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Tip = CreateDefaultSubobject<UStaticMeshComponent>("Tip");
	Tip->AttachToComponent(Bar, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void APryingTool::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APryingTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString APryingTool::ItemName()
{
	return "Prying Tool";
}

FString APryingTool::LoreText()
{
	return "A tool for prying things open. The builders must have left it here by mistake.";
}

