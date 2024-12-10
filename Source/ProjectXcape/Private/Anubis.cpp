// Fill out your copyright notice in the Description page of Project Settings.


#include "Anubis.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAnubis::AAnubis()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	GetCapsuleComponent()->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	AnubisMesh = GetMesh();
	AnubisMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	AnubisMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	GetCapsuleComponent()->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	LeftLight = CreateDefaultSubobject<USpotLightComponent>("LeftLight");
	LeftLight->AttachToComponent(AnubisMesh, FAttachmentTransformRules::KeepRelativeTransform);
	RightLight = CreateDefaultSubobject<USpotLightComponent>("RightLight");
	RightLight->AttachToComponent(AnubisMesh, FAttachmentTransformRules::KeepRelativeTransform);
	
	CurrentWaypointIndex = 0;
}

UBehaviorTree* AAnubis::GetBehaviourTree() const
{
	return Tree;
}

// Called when the game starts or when spawned
void AAnubis::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AProjectXcapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), UAnubisWaypoint::StaticClass(), Waypoints);
}

// Called every frame
void AAnubis::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnubis::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

