

#include <Gameplay/Pawns/DuelPawn.h>

ADuelPawn::ADuelPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	SetReplicateMovement( true );

}

void ADuelPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADuelPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADuelPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADuelPawn::TriggerRPC()
{
	ClientRPCFunction();
}

void ADuelPawn::ClientRPCFunction_Implementation()
{
	DM_LOG( "RPC Called" );
	if(IsLocallyControlled())
	{
		DM_LOG( "Is Locally Controlled" );
	}

	if ( GetLocalRole() == ROLE_Authority )
	{
		DM_LOG( "Is Authority" );
	}
	else
	{
		DM_LOG( "Is Authority" );
	}
}

