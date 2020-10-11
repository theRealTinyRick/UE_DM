

#include <Gameplay/Pawns/DuelPawn.h>
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/GameState.h"
#include <Gameplay/GameState/DMGameState.h>


ADuelPawn::ADuelPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates( true );
	SetReplicateMovement( true );
}

void ADuelPawn::BeginPlay()
{
	Super::BeginPlay();
	GameState = GetWorld()->GetGameState<ADMGameState>();

	if ( GameState != nullptr )
	{
		GameState->GameStartedEvent.AddDynamic( this, &ADuelPawn::OnGameStart );
		GameState->GameEndedEvent.AddDynamic( this, &ADuelPawn::OnGameEnd );

		if ( HasAuthority() )
		{
			if ( IsLocallyControlled() )
			{
				PlayerNumber = 1;
				GameState->PlayerOne = this;
			}
			else
			{
				PlayerNumber = 2;
				GameState->PlayerTwo = this;
			}
		}
		else
		{
			if(IsLocallyControlled())
			{
				PlayerNumber = 2;
				GameState->PlayerTwo = this;
			}
			else
			{
				PlayerNumber = 1;
				GameState->PlayerOne = this;
			}
		}
	}
}

void ADuelPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ADuelPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void ADuelPawn::OnGameStart()
{
	DM_SCREENLOG( *FString::Printf( TEXT("Game Started: Player %i "), PlayerNumber ), 10 );
}

void ADuelPawn::OnGameEnd()
{
	DM_SCREENLOG( *FString::Printf( TEXT("Game Ended: Player %i "), PlayerNumber ), 10 );
}

void ADuelPawn::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const 
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME( ADuelPawn, PlayerNumber );
}