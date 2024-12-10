// Fill out your copyright notice in the Description page of Project Settings.


#include "AnubisWaypoint.h"

// Sets default values
AAnubisWaypoint::AAnubisWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Waypoint = CreateDefaultSubobject<USceneComponent>("Waypoint");
	RootComponent = Waypoint;

}

// Called when the game starts or when spawned
void AAnubisWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnubisWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

