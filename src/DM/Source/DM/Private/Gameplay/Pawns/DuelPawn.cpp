

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
}

void ADuelPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ADuelPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

//void ADuelPawn::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const 
//{
//	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
//	//DOREPLIFETIME( ADuelPawn, PlayerNumber );
//}