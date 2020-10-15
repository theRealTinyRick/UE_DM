// Copyright Epic Games, Inc. All Rights Reserved.

#include "DMGameModeBase.h"

#include "Engine/World.h"
#include <Gameplay/GameState/DMGameState.h>
#include <Gameplay/Actors/ActionManager.h>
#include <Gameplay/Pawns/DuelPawn.h>
#include <Gameplay/Controller/BasePlayerController.h>

void ADMGameModeBase::HandlePlayerStart( APlayerController* PlayerController )
{
	if(PlayerController == nullptr)
	{
		return;
	}
	PlayerController->bShowMouseCursor = true;
	bool bIsServer = PlayerController->IsLocalController();
	
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>( PlayerController );
	if(BasePlayerController == nullptr)
	{
		return;
	}
	
	BasePlayerController->ClientReadyEvent.AddDynamic( this, &ADMGameModeBase::StartGame );

	AActor* PlayerStart = FindPlayerStart( BasePlayerController, bIsServer ? LOCAL_TAG : REMOTE_TAG );
	if(PlayerStart == nullptr)
	{
		DM_SCREENERROR( "Cannot spawn Pawn. No player Start found.", 10 );
		return;
	}

	UWorld* World = GetWorld();
	if(World != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = BasePlayerController;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		APawn* NewPawn = World->SpawnActor<APawn>(DefaultPawnClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParams );
		if(NewPawn != nullptr)
		{
			BasePlayerController->Possess( NewPawn );
			ADuelPawn* DuelPawn = Cast<ADuelPawn>( NewPawn );

			if(bIsServer)
			{
				PlayerOne = DuelPawn != nullptr ? DuelPawn : nullptr;
				PlayerOneController = BasePlayerController;
				BasePlayerController->SetIsServer();
			}
			else
			{
				PlayerTwo = DuelPawn != nullptr ? DuelPawn : nullptr;
				PlayerTwoController = BasePlayerController;
				BasePlayerController->SetIsClient();
			}

			if(PlayerOne != nullptr && PlayerTwo != nullptr)
			{
				SpawnActionManager(BasePlayerController);
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
		
		AActionManager* ActionManager = World->SpawnActor<AActionManager>( AActionManager::StaticClass(), FVector(0, 0, 0), FRotator(0, 0 , 0), SpawnParams );
		SpawnedActionManager = ActionManager;
	}
}

void ADMGameModeBase::StartGame()
{
	if ( PlayerOne != nullptr && PlayerTwo != nullptr )
	{
		PlayerOneController->OnGameStart();
		PlayerTwoController->OnGameStart();

		PostStartGame();
	}
	else
	{
		// repeat this function till both players are ready
		GetWorldTimerManager().SetTimer( TimerHandle, this, &ADMGameModeBase::StartGame, 0.1f, true );
	}
}

