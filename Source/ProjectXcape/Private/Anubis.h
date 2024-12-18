// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnubisWaypoint.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Character.h"
#include "ProjectXcape/ProjectXcapeCharacter.h"
#include "Anubis.generated.h"

UCLASS()
class AAnubis : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnubis();
	UPROPERTY(EditAnywhere)
	USpotLightComponent* LeftLight;
	UPROPERTY(EditAnywhere)
	USpotLightComponent* RightLight;
	TArray<AActor*> TempWaypoints;
	UPROPERTY(EditAnywhere)
	TArray<AAnubisWaypoint*> Waypoints;
	UPROPERTY(EditAnywhere)
	int CurrentWaypointIndex;
	AProjectXcapeCharacter* Player;
	UPROPERTY(EditAnywhere)
	USceneComponent* HitBoxOrigin;
	UPROPERTY(EditAnywhere)
	UBoxComponent* HitBox;
	UPROPERTY(EditAnywhere)
	bool IgnorePlayer;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* RedEyeMat;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* BlueEyeMat;

	//AI
	UBehaviorTree* GetBehaviourTree() const;

	UFUNCTION()
	void PlayAttackMontage();
	UFUNCTION()
	void PlayActivateMontage();
	
	
	//Animation
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnimMontage;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ActivateAnimMontage;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RegisterNotifies();
	void NotifySpawnTrigger();
	void NotifyDespawnTrigger();
	void NotifyHasRisen();
	

	TArray<AAnubisWaypoint*> SortWaypoints(TArray<AActor*> wplist);

	//AI
	UPROPERTY(EditAnywhere, Category ="AI")
	UBehaviorTree* Tree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION( )
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult );
};
