// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ShowName(bool Visible, const FString& Name);
	UFUNCTION(BlueprintImplementableEvent)
	void ShowInspect(bool Visible);
	UFUNCTION(BlueprintImplementableEvent)
	void ShowInteract(bool Visible, const FString& Text);
	UFUNCTION(BlueprintImplementableEvent)
	void ShowPauseMenu(bool Visible);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSelected(int index);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateItem(const FString& Name);
	UFUNCTION(BlueprintImplementableEvent)
	void ShowLore(const FString& Text, float time);
	UPROPERTY(BlueprintReadWrite)
	float mouseSensitivity = 1.0f;
	UPROPERTY(BlueprintReadWrite)
	float volume = 1.0f;
};
