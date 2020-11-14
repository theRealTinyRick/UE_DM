// Fill out your copyright notice in the Description page of Project Settings.


#include <Gameplay/Actors/ActionManager.h>
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include <Components/SceneComponent.h>

#include <Framework/Card/Card.h>
#include <Framework/Card/CardIdentity.h>
#include <Framework/Card/CardLocation.h>
#include <Framework/Card/CardCollection.h>
#include <Framework/Duelist/Duelist.h>

#include <Gameplay/Pawns/DuelPawn.h>
#include <Gameplay/GameState/DMGameState.h>
#include <Gameplay/Controller/BasePlayerController.h>


AActionManager::AActionManager()

{
	USceneComponent* NewRoot = CreateDefaultSubobject<USceneComponent>( TEXT( "Root Component" ) );
	SetRootComponent( NewRoot );

	PrimaryActorTick.bCanEverTick = true;
	SetReplicates( true );
}

void AActionManager::BeginPlay()
{
	Super::BeginPlay();
}

void AActionManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}


void AActionManager::LocatePlayerPawns()
{
	if ( PlayerOne != nullptr && PlayerTwo != nullptr )
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass( GetWorld(), ADuelPawn::StaticClass(), FoundActors );

	if(FoundActors.Num() == 0)
	{
		DM_SCREENLOG( "Players not found", 10 );
		return;
	}

	for ( AActor* Actor : FoundActors )
	{
		ADuelPawn* Pawn = Cast<ADuelPawn>( Actor );
		if ( Pawn->PlayerNumber == 1 )
		{
			PlayerOne = Pawn;
		}
		else if ( Pawn->PlayerNumber == 2 )
		{
			PlayerTwo = Pawn;
		}
	}

	for ( AActor* Actor : FoundActors )
	{
		ADuelPawn* Pawn = Cast<ADuelPawn>( Actor );
		if ( !Pawn->GetIsPlayerNumberSet() )
		{
			Pawn->SetPlayerNumber( PlayerOne == nullptr ? 1 : 2 );
			if ( Pawn->PlayerNumber == 1 )
			{
				PlayerOne = Pawn;
			}
			else if ( Pawn->PlayerNumber == 2 )
			{
				PlayerTwo = Pawn;
			}
		}
	}

	/*if ( PlayerOne != nullptr )
	{
		DM_SCREENLOG( "Found player: 1", 10 );
	}

	if ( PlayerTwo != nullptr )
	{
		DM_SCREENLOG( "Found player: 2", 10 );
	}*/
}


ADuelPawn* AActionManager::GetPlayerByNumber( int Number )
{
	if ( Number == -1 )
	{
		DM_ERROR( "[AActionManager::GetPlayerByNumber]: Number passed in is -1." );
		return nullptr;
	}

	return Number == 1 ? PlayerOne : PlayerTwo;
}

void AActionManager::ActionName_Implementation( const TArray<FString>& Cards )
{
	// setup a queeu
	ActionName_Execute( Cards );
}


void AActionManager::ActionName_Execute_Implementation( const TArray<FString>& Cards )
{
		//ACTION_EXECUTE_START
		//TODO: Add your logic here
		//ACTION_EXECUTE_END

		for ( FString Card : Cards )
		{
			DM_SCREENLOG( *Card, 10 );
		}

	/*if (IsLocallyControlled())
	{
		DM_SCREENLOG("Is Locally Controlled", 10);
	}
	else
	{
		DM_SCREENERROR("Is NOT Locally Controlled", 10);
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		DM_SCREENLOG("Is Authority", 10);
	}
	else
	{
		DM_SCREENERROR("Is NOT Authority", 10);
	}*/
}



void AActionManager::AddShield_Implementation( int TargetPlayerNumber, int AmountToAdd /*= 1 */ )
{
	AddShield_Execute( TargetPlayerNumber, AmountToAdd );
}

void AActionManager::AddShield_Execute_Implementation( int TargetPlayerNumber, int AmountToAdd /*= 1 */ )
{
	ACTION_EXECUTE
	UCardCollection* Deck = TargetPawn->GetDuelist()->GetCollection( ECardLocation::DECK );
	UCardCollection* ShieldZone = TargetPawn->GetDuelist()->GetCollection( ECardLocation::SHIELDZONE );

	if ( Deck->GetCards().Num() <= 0 )
	{
		//TODO: add event to show that cards can't be added
		DM_SCREENERROR( "No Cards To Add", 5 );
		return;
	}

	for ( int i = 0; i < AmountToAdd; i++ )
	{
		if ( Deck->GetCards().Num() > 0 )
		{
			UCard* Card = Deck->GetCards()[0];
			if ( Card != nullptr )
			{
				Deck->RemoveCard( Card );
				ShieldZone->AddCard( Card );
				Card->CurrentLocation = ECardLocation::SHIELDZONE;
				Card->PreviousLocation = ECardLocation::DECK;
				ShieldAddedEvent.Broadcast( Card, TargetPawn->GetDuelist() );
			}
		}
		else
		{
			break;
		}
	}
	//TODO: make the player add shield deterministically
}



void AActionManager::Draw_Implementation( int TargetPlayerNumber, int AmountToDraw /*= 1*/ )
{
	Draw_Execute( TargetPlayerNumber, AmountToDraw );
}

void AActionManager::Draw_Execute_Implementation( int TargetPlayerNumber, int AmountToDraw /*= 1 */ )
{
	ACTION_EXECUTE
		
	UCardCollection* Deck = TargetPawn->GetDuelist()->GetCollection( ECardLocation::DECK );
	UCardCollection* Hand = TargetPawn->GetDuelist()->GetCollection( ECardLocation::HAND );

	if(Deck->GetCards().Num() <= 0)
	{
		//TODO: add event to show that cards can't be drawn
		DM_SCREENERROR( "No Cards To Draw", 5 );
		return;
	}

	for ( int i = 0; i < AmountToDraw; i++ )
	{
		if(Deck->GetCards().Num() > 0)
		{
			UCard* Card = Deck->GetCards()[0];
			if(Card	!= nullptr)
			{
				Deck->RemoveCard( Card );
				Hand->AddCard( Card );
				Card->CurrentLocation = ECardLocation::HAND;
				Card->PreviousLocation = ECardLocation::DECK;

				CardDrawnEvent.Broadcast(Card, TargetPawn->GetDuelist());
			}
		}
		else
		{
			//TODO: add event to show that cards can't be drawn
			break;
		}
	}
}