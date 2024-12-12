// Fill out your copyright notice in the Description page of Project Settings.


#include "HugeBrazier.h"

#include "GemYellow.h"
#include "Torch.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"

// Sets default values
AHugeBrazier::AHugeBrazier()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	Brazier = CreateDefaultSubobject<UStaticMeshComponent>("Brazier");
	Brazier->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	LightSource = CreateDefaultSubobject<UPointLightComponent>("LightSource");
	LightSource->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	for (int32 i = 0; i < 6; i++)
	{
		FString ComponentName = FString::Printf(TEXT("Fire_%d"), i);
		UNiagaraComponent* FlameComp = CreateDefaultSubobject<UNiagaraComponent>(*ComponentName);
		FlameComp->SetupAttachment(Root);
		FlameComp->SetAutoActivate(false); // Disable initially
		Fires.Add(FlameComp);
	}
	IsLit = false;
	currentColor = EFlameColor::Orange;
	
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHugeBrazier::BeginPlay()
{
	Player = Cast<AProjectXcapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	LightSource->SetLightFunctionMaterial(LightFunctions[FMath::RandRange(0,4)]);

	LightSource->SetVisibility(false);
	Super::BeginPlay();
	
}

void AHugeBrazier::Interact()
{
	auto Torch = Cast<ATorch>(Player->Inventory[Player->CurrentItemIndex]);
	auto Gem = Cast<AGemYellow>(Player->Inventory[Player->CurrentItemIndex]);
	if (Torch)
	{
		if (IsLit && !Torch->IsLit)
		{
			Torch->LightTorch();
		}
		else if (!IsLit && Torch->IsLit)
		{
			LightFire();
		}
	}
	else if(Gem && IsLit)
	{
		int color = 0;
		if (Gem->Name == "Yellow Gem") color = 1;
		else if (Gem->Name == "Red Gem") color = 2;
		else if (Gem->Name == "Blue Gem") color = 3;
		switch (currentColor)
		{
		case EFlameColor::Orange:
			{
				switch (color)
				{
					case 1:
						{
							currentColor = EFlameColor::Yellow;
							Fire(1);
							LightSource->LightColor = FColor::Yellow;
							break;
						}
					case 2:
						{
							currentColor = EFlameColor::Red;
							Fire(2);
							LightSource->LightColor = FColor::Red;
							break;
						}
					case 3:
						{
							currentColor = EFlameColor::Blue;
							Fire(3);
							LightSource->LightColor = FColor::Blue;
							break;
						}
				default:
						{
							break;
						}
				}
			}
		case EFlameColor::Red:
			{
				switch (color)
				{
				case 1:
					{
						currentColor = EFlameColor::Orange;
						Fire(0);
						LightSource->LightColor = FColor::Orange;
						break;
					}
				case 3:
					{
						currentColor = EFlameColor::Purple;
						Fire(4);
						LightSource->LightColor = FColor::Purple;
						OpenDoor(PurpleDoor);
						break;
					}
				default:
					{
						break;
					}
				}
				break;
			}
		case EFlameColor::Blue:
			{
				switch (color)
				{
				case 1:
					{
						currentColor = EFlameColor::Green;
						Fire(5);
						LightSource->LightColor = FColor::Green;
						OpenDoor(GreenDoor);
						break;
					}
				case 2:
					{
						currentColor = EFlameColor::Purple;
						Fire(4);
						LightSource->LightColor = FColor::Purple;
						OpenDoor(PurpleDoor);
						break;
					}
				default:
					{
						break;
					}
				}
				break;
			}
		case EFlameColor::Yellow:
			{
				switch (color)
				{
				case 2:
					{
						currentColor = EFlameColor::Orange;
						Fire(0);
						LightSource->LightColor = FColor::Orange;
						break;
					}
				case 3:
					{
						currentColor = EFlameColor::Green;
						Fire(5);
						LightSource->LightColor = FColor::Green;
						OpenDoor(GreenDoor);
						break;
					}
				default:
					{
						break;
					}
				}
				break;
			}
		default:
			{
				break;
			}
		}
		
		
	}
	else if (IsLit)
	{
		for (UNiagaraComponent* Fire : Fires)
		{
			Fire->Deactivate();
		}
		currentColor = EFlameColor::Orange;
		LightSource->SetVisibility(false);
		IsLit = false;
	}
}

FString AHugeBrazier::ShowInteractText()
{
	FString string = "";

	auto Torch = Cast<ATorch>(Player->Inventory[Player->CurrentItemIndex]);
	auto Gem = Cast<AGemYellow>(Player->Inventory[Player->CurrentItemIndex]);
	if (Torch)
	{
		if (IsLit && !Torch->IsLit)
		{
			string = "R to Light Torch";
		}
		else if (!IsLit && Torch->IsLit)
		{
			string = "R to Light Brazier";
		}
	}
	else if(Gem && IsLit)
	{
		string = "R to Use " + Gem->Name;
	}
	else if (IsLit)
	{
		string = "R to Extinguish";
	}
	return string;
	
}

FString AHugeBrazier::ShowName()
{
	return "Huge Brazier";
}

void AHugeBrazier::LightFire()
{
	Fire(0);
	LightSource->LightColor = FColor::Orange;
	LightSource->SetVisibility(true);
	IsLit = true;
}

void AHugeBrazier::OpenDoor(AActor* Door)
{
	if(auto DoorComp = Cast<USceneComponent>(Door->GetRootComponent()))
	{
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this; 
		FVector doorPos = DoorComp->GetRelativeLocation();
		FRotator doorRot = DoorComp->GetRelativeRotation();
	
		FVector openPos = doorPos - FVector(0, 250,0);
	
		UKismetSystemLibrary::MoveComponentTo(DoorComp, openPos, doorRot, true, true, 5.f, false, EMoveComponentAction::Move, LatentInfo);

	}
	
}

void AHugeBrazier::Fire(int i)
{
	for (UNiagaraComponent* Fire : Fires)
	{
		Fire->Deactivate();
	}
	Fires[i]->ActivateSystem();
}


// Called every frame
void AHugeBrazier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

