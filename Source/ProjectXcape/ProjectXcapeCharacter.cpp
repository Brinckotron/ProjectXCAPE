// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectXcapeCharacter.h"

#include <string>

#include "ProjectXcapeProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "Private/PlayerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Tests/AutomationCommon.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectXcapeCharacter

AProjectXcapeCharacter::AProjectXcapeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	InspectOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("InspectOrigin"));
	InspectOrigin->SetupAttachment(FirstPersonCameraComponent);
	InspectOrigin->SetRelativeLocation(FVector(40.f, 0.f, 0.f));
	HoldOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("HoldOrigin"));
	HoldOrigin->SetupAttachment(FirstPersonCameraComponent);
	HoldOrigin->SetRelativeLocation(FVector(30.f, 20.f, -10.f));
	pauseSelectIndex = 0;
	mouseSensitivity = 1.f;

}

void AProjectXcapeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	auto UserWidget = CreateWidget(GetWorld(), PlayerWidgetClass);
	PlayerWidget = Cast<UPlayerWidget>(UserWidget);
	PlayerWidget->AddToViewport();
	PlayerWidget->ShowInteract(false, "");
	PlayerWidget->ShowInspect(false);
	PlayerWidget->ShowHold(false);
	PlayerWidget->ShowPauseMenu(false);
	InitialItemTransform = GetActorTransform();
	
}

//////////////////////////////////////////////////////////////////////////// Input

void AProjectXcapeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::Look);

		EnhancedInputComponent->BindAction(HoldAction, ETriggerEvent::Started, this, &AProjectXcapeCharacter::HoldItem);
		
		EnhancedInputComponent->BindAction(InspectEnterAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::InspectEnter);

		EnhancedInputComponent->BindAction(InspectExitAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::InspectExit);

		EnhancedInputComponent->BindAction(InspectRotateAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::InspectRotate);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &AProjectXcapeCharacter::Pause);

		EnhancedInputComponent->BindAction(SelectUpAction, ETriggerEvent::Started, this, &AProjectXcapeCharacter::SelectUp);

		EnhancedInputComponent->BindAction(SelectDownAction, ETriggerEvent::Started, this, &AProjectXcapeCharacter::SelectDown);

		EnhancedInputComponent->BindAction(SelectLeftAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::SelectLeft);

		EnhancedInputComponent->BindAction(SelectRightAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::SelectRight);
		
		EnhancedInputComponent->BindAction(ConfirmSelectAction, ETriggerEvent::Started, this, &AProjectXcapeCharacter::ConfirmSelect);

		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectXcapeCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsInspecting && !UGameplayStatics::IsGamePaused(GetWorld()))
	{
		FHitResult Hit;
		FVector Start = FirstPersonCameraComponent->GetComponentLocation();
		FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * 150.f;
		
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		
		if(GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams, QueryParams) && IsValid(Hit.GetActor()) && Hit.GetActor()->ActorHasTag("Inspectable"))
		{
			CurrentInteractActor = Hit.GetActor();
			PlayerWidget->ShowInteract(true, FString(Hit.Component->GetName()));

			if (CurrentInteractActor->ActorHasTag("Inspectable") && !IsHolding)
			{
				PlayerWidget->ShowInspect(true);
			}
			if (CurrentInteractActor->ActorHasTag("Holdable") && !IsHolding)
			{
				PlayerWidget->ShowHold(true);
			}
		}
		else
		{
			CurrentInteractActor = nullptr;
			PlayerWidget->ShowInteract(false, "");
			PlayerWidget->ShowInspect(false);
			PlayerWidget->ShowHold(false);
		}
	}
}


void AProjectXcapeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AProjectXcapeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X * mouseSensitivity);
		AddControllerPitchInput(LookAxisVector.Y * mouseSensitivity);
	}
}

void AProjectXcapeCharacter::InspectEnter()
{
	auto PlayerController = Cast<APlayerController>(GetController());
	auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	

	if (!IsInspecting && !IsHolding && CurrentInteractActor != nullptr && CurrentInteractActor->ActorHasTag("Interactible"))
	{
		InputSubsystem->RemoveMappingContext(DefaultMappingContext);
		InputSubsystem->AddMappingContext(InspectMappingContext, 0);
		IsInspecting = true;
		PlayerWidget->ShowInteract(false, "");
		PlayerWidget->ShowHold(false);
		PlayerWidget->ShowInspect(false);
		InspectOrigin->SetRelativeRotation(FRotator::ZeroRotator);
		InitialItemTransform = CurrentInteractActor->GetActorTransform();
		CurrentInteractActor->AttachToComponent(InspectOrigin, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AProjectXcapeCharacter::InspectExit()
{
	if(IsInspecting)
	{
		IsInspecting = false;
		if (CurrentInteractActor != nullptr)
		{
			CurrentInteractActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			CurrentInteractActor->SetActorTransform(InitialItemTransform);
		}
		CurrentInteractActor = nullptr;
	
		auto PlayerController = Cast<APlayerController>(GetController());
		auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		InputSubsystem->RemoveMappingContext(InspectMappingContext);
		InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
}

void AProjectXcapeCharacter::InspectRotate(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	InspectOrigin->SetRelativeRotation(InspectOrigin->GetRelativeRotation() + FRotator(LookAxisVector.Y, LookAxisVector.X, 0));
}

void AProjectXcapeCharacter::HoldItem()
{
	if (IsHolding)
	{
		DropItem();
		return;
	}
	
	if (!IsHolding && CurrentInteractActor != nullptr && CurrentInteractActor->ActorHasTag("Holdable"))
	{
		IsHolding = true;
		PlayerWidget->ShowInteract(false, "");
		PlayerWidget->ShowInspect(false);
		PlayerWidget->ShowHold(false);
		InspectOrigin->SetRelativeRotation(FRotator::ZeroRotator);
		CurrentHeldItem = CurrentInteractActor;
		InitialItemTransform = CurrentHeldItem->GetActorTransform();
		CurrentHeldItem->AttachToComponent(HoldOrigin, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AProjectXcapeCharacter::DropItem()
{
	IsHolding = false;
	if (CurrentHeldItem != nullptr)
	{
		CurrentHeldItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentHeldItem->SetActorTransform(InitialItemTransform);
	}
	CurrentHeldItem = nullptr;
}

void AProjectXcapeCharacter::PlaceItem()
{
}

void AProjectXcapeCharacter::Pause()
{

	if (GetWorld())
	{
		bool isPaused = UGameplayStatics::IsGamePaused(GetWorld());
		UGameplayStatics::SetGamePaused(GetWorld(), !isPaused);
		PlayerWidget->ShowInteract(false, "");
		PlayerWidget->ShowInspect(false);
		PlayerWidget->ShowHold(false);
		PlayerWidget->ShowPauseMenu(!isPaused);
		pauseSelectIndex = 0;
		PlayerWidget->UpdateSelected(pauseSelectIndex);
		auto PlayerController = Cast<APlayerController>(GetController());
		auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		InputSubsystem->RemoveMappingContext(isPaused? PauseMappingContext : InspectMappingContext);
		InputSubsystem->AddMappingContext(isPaused? (IsInspecting? InspectMappingContext: DefaultMappingContext ) : PauseMappingContext, 0);
	}
}

void AProjectXcapeCharacter::SelectUp()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		if (pauseSelectIndex > 0)
		{
			pauseSelectIndex--;
			PlayerWidget->UpdateSelected(pauseSelectIndex);
		}
	}
}

void AProjectXcapeCharacter::SelectDown()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		if (pauseSelectIndex < 3)
		{
			pauseSelectIndex++;
			PlayerWidget->UpdateSelected(pauseSelectIndex);
		}
	}
}

void AProjectXcapeCharacter::SelectLeft()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		switch (pauseSelectIndex)
		{
		case 2:
			{
				
				break;
			}
		case 3:
			{
				if (mouseSensitivity > 0.09f) mouseSensitivity -= 0.05f;
				PlayerWidget->mouseSensitivity = mouseSensitivity;
				break;
			}
		default:
			{
				break;
			}
		}
	}	
}

void AProjectXcapeCharacter::SelectRight()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		switch (pauseSelectIndex)
		{
		case 2:
			{
				
				break;
			}
		case 3:
			{
				if (mouseSensitivity < 2) mouseSensitivity += 0.05f;
				PlayerWidget->mouseSensitivity = mouseSensitivity;
				break;
			}
		default:
			{
				break;
			}
		}
	}	
}

void AProjectXcapeCharacter::ConfirmSelect()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		switch (pauseSelectIndex)
		{
		case 0:
			{
				Pause();
				break;
			}
		case 1:
			{
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit,true);
				break;
			}
		default:
			{
				break;
			}
		}
	}
}

