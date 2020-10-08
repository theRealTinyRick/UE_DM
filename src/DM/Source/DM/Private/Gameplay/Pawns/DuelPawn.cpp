

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

void ADuelPawn::TriggerRPC_Server()
{
	ServerRPCFunction();
}

void ADuelPawn::MulticastRPCFunction_Implementation()
{
	DM_SCREENLOG("MC RPC Called", 10);
}

void ADuelPawn::ServerRPCFunction_Implementation()
{
	DM_SCREENLOG("SERVER RPC Called", 10);
	MulticastRPCFunction();
	
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

