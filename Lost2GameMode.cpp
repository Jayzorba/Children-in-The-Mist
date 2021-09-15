// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lost2GameMode.h"
#include "Lost2HUD.h"
#include "Lost2Character.h"
#include "UObject/ConstructorHelpers.h"

ALost2GameMode::ALost2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Levels/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALost2HUD::StaticClass();
}
