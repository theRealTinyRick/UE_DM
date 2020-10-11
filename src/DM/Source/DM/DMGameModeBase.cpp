// Copyright Epic Games, Inc. All Rights Reserved.

#include "DMGameModeBase.h"

#include "Engine/World.h"
#include <Gameplay/GameState/DMGameState.h>
#include <Gameplay/Actors/ActionManager.h>
#include <Gameplay/Pawns/DuelPawn.h>

void ADMGameModeBase::HandlePlayerStart( APlayerController* PlayerController )
{
	if(PlayerController == nullptr)
	{
		return;
	}
	PlayerController->bShowMouseCursor = true;
	
	AActor* PlayerStart = FindPlayerStart( PlayerController, PlayerController->IsLocalController() ? LOCAL_TAG : REMOTE_TAG );
	if(PlayerStart == nullptr)
	{
		DM_SCREENERROR( "Cannot spawn Pawn. No player Start found.", 10 );
		return;
	}

	UWorld* World = GetWorld();
	if(World != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = PlayerController;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		APawn* NewPawn = World->SpawnActor<APawn>(DefaultPawnClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParams );
		if(NewPawn != nullptr)
		{
			PlayerController->Possess( NewPawn );
			ADuelPawn* DuelPawn = Cast<ADuelPawn>( NewPawn );

			if(PlayerController->IsLocalController())
			{
				PlayerOne = DuelPawn != nullptr ? DuelPawn : nullptr;
			}
			else
			{
				PlayerTwo = DuelPawn != nullptr ? DuelPawn : nullptr;
			}

			if(PlayerOne != nullptr && PlayerTwo != nullptr)
			{
				SpawnActionManager(PlayerController);
			}
		}
	}
}

void ADMGameModeBase::SpawnActionManager( APlayerController* NewOwner )
{
	UWorld* World = GetWorld();
	if ( World != nullptr )
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = NewOwner;
		
		TSubclassOf<AActionManager> ActionManagerClass = AActionManager::StaticClass();
		AActionManager* ActionManager = World->SpawnActor<AActionManager>( ActionManagerClass, FVector(0, 0, 0), FRotator(0, 0 , 0), SpawnParams );
		
		if(ActionManager != nullptr)
		{
			SpawnedActionManager = ActionManager;
			ActionManager->FinishedPingEvent.AddDynamic( this, &ADMGameModeBase::StartGame );
			ActionManager->StartClientPing();
		}
	}
}

void ADMGameModeBase::StartGame()
{
	 ADMGameState* DMGameState = GetGameState<ADMGameState>();
	 if(DMGameState == nullptr)
	 {
		 DM_SCREENERROR( "[ADMGameModeBase] Cannot start game with out properly setting up the gamestate class.", 10 );
		 DM_ERROR( "[ADMGameModeBase] Cannot start game with out properly setting up the gamestate class.");
		 return;
	 }

	 DMGameState->bIsServer = true;
	 DMGameState->StartGame();

	PostStartGame();
}

