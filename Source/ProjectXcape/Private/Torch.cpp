// Fill out your copyright notice in the Description page of Project Settings.


#include "Torch.h"

// Sets default values
ATorch::ATorch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TorchHandle = CreateDefaultSubobject<UStaticMeshComponent>("TorchHandle");
	RootComponent = TorchHandle;
	TorchTip = CreateDefaultSubobject<UStaticMeshComponent>("TorchTip");
	TorchTip->AttachToComponent(TorchHandle, FAttachmentTransformRules::KeepRelativeTransform);
	TorchFlame = CreateDefaultSubobject<UNiagaraComponent>("TorchFlame");
	TorchFlame->AttachToComponent(TorchTip, FAttachmentTransformRules::KeepRelativeTransform);
	TorchLight = CreateDefaultSubobject<UPointLightComponent>("TorchLight");
	TorchLight->AttachToComponent(TorchTip, FAttachmentTransformRules::KeepRelativeTransform);
	IsLit = false;

}

// Called when the game starts or when spawned
void ATorch::BeginPlay()
{
	Super::BeginPlay();
	TorchLight->SetVisibility(false);
	
}

// Called every frame
void ATorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ATorch::ItemName()
{
	return "Torch";
}

void ATorch::LightTorch()
{
	TorchFlame->ActivateSystem();
	TorchLight->SetVisibility(true);
	IsLit = true;
	
}

void ATorch::ExtinguishTorch()
{
	TorchFlame->Deactivate();
	TorchLight->SetVisibility(false);
	IsLit = false;
}

FString ATorch::LoreText()
{
	return "";
}
