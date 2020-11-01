// Fill out your copyright notice in the Description page of Project Settings.


#include <Gameplay/Controller/BasePlayerController.h>
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include <Gameplay/GameState/DMGameState.h>
#include <Gameplay/Pawns/DuelPawn.h>
#include <Gameplay/Actors/ActionManager.h>

ABasePlayerController::ABasePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABasePlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	OnReceivedPlayer();
}

void ABasePlayerController::PlayerTick( float DeltaTime )
{
	Super::PlayerTick( DeltaTime );

	if(ActionManager == nullptr)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass( GetWorld(), AActionManager::StaticClass(), FoundActors );
		if(FoundActors.Num() == 0)
		{
			return;
		}
		ActionManager = Cast<AActionManager>( FoundActors[0] );
	}

	if(DuelPawn == nullptr)
	{
		ADuelPawn* NewDuelPawn = GetPawn<ADuelPawn>();
		if ( NewDuelPawn == nullptr )
		{
			return;
		}
		DuelPawn = NewDuelPawn;
		DuelPawn->SetPlayerNumber( PlayerNumber );
	}

	if( !bShouldStartReadying )
	{
		return;
	}

	if ( !bHasSentServerReady )
	{
		if(ActionManager == nullptr || DuelPawn == nullptr)
		{
			return;
		}

		if(bIsClient)
		{
			SendClientReadyToServer();
		}
		bHasSentServerReady = true;
	}
}

void ABasePlayerController::SendClientReadyToServer_Implementation()
{
	ClientReadyEvent.Broadcast();
}

void ABasePlayerController::OnGameStart_Implementation()
{
	DM_SCREENERROR(  FString::Printf(TEXT( "On Game Start    %i" ), PlayerNumber) , 10 );
	GameStartEvent.Broadcast();
}

void ABasePlayerController::SetIsClient_Implementation()
{
	bIsClient = true;
	bShouldStartReadying = true;
	PlayerNumber = 2;
}

void ABasePlayerController::SetIsServer()
{
	bIsServer = true;
	bShouldStartReadying = true;
	PlayerNumber = 1;
}

//void ABasePlayerController::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const
//{
//	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
//	//DOREPLIFETIME( ABasePlayerController, PlayerNumber );
//}