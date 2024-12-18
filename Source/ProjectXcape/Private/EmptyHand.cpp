// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyHand.h"

// Sets default values
AEmptyHand::AEmptyHand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEmptyHand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmptyHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AEmptyHand::ItemName()
{
	return "";
}

FString AEmptyHand::LoreText()
{
	return "";
}

