// Fill out your copyright notice in the Description page of Project Settings.

#include "DuelGameMode.h"
#include <Gameplay/Pawns/DuelPawn.h>
#include <Gameplay/Actors/ActionManager.h>

#define STARTING_HAND_COUNT 5
#define STARTING_SHIELD_COUNT 5
#define MAX_HAND_COUNT 10

void ADuelGameMode::SetupGame()
{
	Super::SetupGame();
	//OnGameSetup();

	if(SpawnedActionManager!= nullptr)
	{
		SpawnedActionManager->AddShield( 1, STARTING_HAND_COUNT );
		SpawnedActionManager->AddShield( 2, STARTING_HAND_COUNT );

		SpawnedActionManager->Draw( 1, STARTING_HAND_COUNT );
		SpawnedActionManager->Draw( 2, STARTING_HAND_COUNT );
	}
}
