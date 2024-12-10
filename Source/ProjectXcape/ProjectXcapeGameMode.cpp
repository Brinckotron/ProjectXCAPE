// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectXcapeGameMode.h"
#include "ProjectXcapeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectXcapeGameMode::AProjectXcapeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = AProjectXcapeCharacter::StaticClass();

}
