// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectXcapeCharacter.h"
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

}

void AProjectXcapeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	auto UserWidget = CreateWidget(GetWorld(), PlayerWidgetClass);
	PlayerWidget = Cast<UPlayerWidget>(UserWidget);
	PlayerWidget->AddToViewport();
	PlayerWidget->SetPromptF(false);
	InitialInspectTransform = GetActorTransform();
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

		EnhancedInputComponent->BindAction(InspectEnterAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::InspectEnter);

		EnhancedInputComponent->BindAction(InspectExitAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::InspectExit);

		EnhancedInputComponent->BindAction(InspectRotateAction, ETriggerEvent::Triggered, this, &AProjectXcapeCharacter::InspectRotate);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &AProjectXcapeCharacter::Pause);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectXcapeCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsInspecting)
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
			CurrentInspectorActor = Hit.GetActor();
			PlayerWidget->SetPromptF(true);
		}
		else
		{
			CurrentInspectorActor = nullptr;
			PlayerWidget->SetPromptF(false);
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
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectXcapeCharacter::InspectEnter()
{
	auto PlayerController = Cast<APlayerController>(GetController());
	auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	

	if (!IsInspecting && CurrentInspectorActor != nullptr && CurrentInspectorActor->ActorHasTag("Inspectable"))
	{
		InputSubsystem->RemoveMappingContext(DefaultMappingContext);
		InputSubsystem->AddMappingContext(InspectMappingContext, 0);
		IsInspecting = true;
		PlayerWidget->SetPromptF(false);
		InspectOrigin->SetRelativeRotation(FRotator::ZeroRotator);
		InitialInspectTransform = CurrentInspectorActor->GetActorTransform();
		CurrentInspectorActor->AttachToComponent(InspectOrigin, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AProjectXcapeCharacter::InspectExit()
{
	IsInspecting = false;
	if (CurrentInspectorActor != nullptr)
	{
		CurrentInspectorActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentInspectorActor->SetActorTransform(InitialInspectTransform);
	}
	CurrentInspectorActor = nullptr;
	
	auto PlayerController = Cast<APlayerController>(GetController());
	auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	InputSubsystem->RemoveMappingContext(InspectMappingContext);
	InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
}

void AProjectXcapeCharacter::InspectRotate(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	InspectOrigin->SetRelativeRotation(InspectOrigin->GetRelativeRotation() + FRotator(LookAxisVector.Y, LookAxisVector.X, 0));
	
}

void AProjectXcapeCharacter::Pause()
{

	if (GetWorld())
	{
		UGameplayStatics::SetGamePaused(GetWorld(), !UGameplayStatics::IsGamePaused(GetWorld()));
	}
}

