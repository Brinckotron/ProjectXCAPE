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
		FlameComp->SetAutoActivate(false);
		Fires.Add(FlameComp);
	}
	IsLit = false;
	IsGreenDoorOpen = false;
	IsPurpleDoorOpen = false;
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
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Yellow"), true);
							ChangeLightColor(FColor::Yellow);
							return;
						}
					case 2:
						{
							currentColor = EFlameColor::Red;
							Fire(2);
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Red"), true);
							ChangeLightColor(FColor::Red);
							return;
						}
					case 3:
						{
							currentColor = EFlameColor::Blue;
							Fire(3);
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Blue"), true);
							ChangeLightColor(FColor::Blue);
							return;
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
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Orange"), true);
						ChangeLightColor(FColor::Orange);
						return;
					}
				case 3:
					{
						currentColor = EFlameColor::Purple;
						Fire(4);
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Purple"), true);
						ChangeLightColor(FColor::Purple);
						OpenDoor(PurpleDoor);
						return;
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
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Green"), true);
						ChangeLightColor(FColor::Green);
						OpenDoor(GreenDoor);
						return;
					}
				case 2:
					{
						currentColor = EFlameColor::Purple;
						Fire(4);
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Purple"), true);
						ChangeLightColor(FColor::Purple);
						OpenDoor(PurpleDoor);
						return;
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
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Orange"), true);
						ChangeLightColor(FColor::Orange);
						return;
					}
				case 3:
					{
						currentColor = EFlameColor::Green;
						Fire(5);
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Green"), true);
						ChangeLightColor(FColor::Green);
						OpenDoor(GreenDoor);
						return;
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
		ChangeLightColor(FColor::Orange);
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
			string = "Click to Light Torch";
		}
		else if (!IsLit && Torch->IsLit)
		{
			string = "Click to Light Brazier";
		}
	}
	else if(Gem && IsLit)
	{
		if ((Gem->Name == "Yellow Gem" && currentColor != EFlameColor::Yellow && currentColor != EFlameColor::Purple && currentColor != EFlameColor::Green)
			|| (Gem->Name == "Red Gem" && currentColor != EFlameColor::Red && currentColor != EFlameColor::Purple && currentColor != EFlameColor::Green)
			|| (Gem->Name == "Blue Gem" && currentColor != EFlameColor::Blue && currentColor != EFlameColor::Purple && currentColor != EFlameColor::Green))
		string = "Click to Use " + Gem->Name;
	}
	else if (IsLit)
	{
		string = "Click to Extinguish";
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
	ChangeLightColor(FColor::Orange);
	LightSource->SetVisibility(true);
	IsLit = true;
}

void AHugeBrazier::OpenDoor(AActor* Door)
{
	if(auto DoorComp = Cast<USceneComponent>(Door->GetRootComponent()))
	{
		if(Door == GreenDoor && IsGreenDoorOpen) return;
		if(Door == PurpleDoor && IsPurpleDoorOpen) return;
		Door == GreenDoor? IsGreenDoorOpen = true : IsPurpleDoorOpen = true;
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

void AHugeBrazier::ChangeLightColor(FColor color)
{
	LightSource->SetVisibility(false);
	LightSource->LightColor = color;
	LightSource->SetVisibility(true);
	
}


// Called every frame
void AHugeBrazier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AHugeBrazier::InspectLore()
{
	return "This flame seems key. Perhaps it must burn with purpose...";
}

