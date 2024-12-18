// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneTablet.h"

// Sets default values
AStoneTablet::AStoneTablet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tablet = CreateDefaultSubobject<UStaticMeshComponent>("Tablet");
	RootComponent = Tablet;

	TabletName = "Stone Tablet";
	
}

// Called when the game starts or when spawned
void AStoneTablet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStoneTablet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AStoneTablet::ItemName()
{
	return TabletName;
}

FString AStoneTablet::LoreText()
{
	return "";
}

