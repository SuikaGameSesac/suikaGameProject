// Copyright Epic Games, Inc. All Rights Reserved.

#include "socketNetworkTestGameMode.h"
#include "socketNetworkTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AsocketNetworkTestGameMode::AsocketNetworkTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
