// Fill out your copyright notice in the Description page of Project Settings.


#include <Gameplay/GameState/DMGameState.h>
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void ADMGameState::StartGame_Implementation()
{
	StartGame_Execute();
}

void ADMGameState::StartGame_Execute()
{
	if( SpawnedActionManager == nullptr || PlayerOne == nullptr || PlayerTwo == nullptr )
	{
		// we know its not ready to start
		GetWorldTimerManager().SetTimer( TimerHandle_DefaultTimer, this, &ADMGameState::StartGame_Execute, 1.0f);
		return;
	}

	GameStartedEvent.Broadcast();

	if(!bIsServer)
	{
		DM_SCREENLOG( "Notifying the server", 10 );
		NotifyServerReadyToStart();
	}
}

void ADMGameState::EndGame_Implementation()
{
	GameEndedEvent.Broadcast();
}

void ADMGameState::NotifyServerReadyToStart_Implementation()
{
	DM_SCREENLOG( "Everyone is ready to set the game table up", 10 );
}