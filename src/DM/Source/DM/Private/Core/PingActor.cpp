// Fill out your copyright notice in the Description page of Project Settings.


#include <Core/PingActor.h>

APingActor::APingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates( true );
}

void APingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ( bStartedPinging && bIsServer )
	{
		PingClient();
	}
}

void APingActor::StartClientPing()
{
	bIsServer = true;
	bStartedPinging = true;
}

void APingActor::PingClient_Implementation()
{
	if ( !bIsServer )
	{
		PingServer();
	}
}

void APingActor::PingServer_Implementation()
{
	if ( bIsServer && bStartedPinging )
	{
		bHasRecievedResponsePing = true;
		bStartedPinging = false;
		FinishedPingEvent.Broadcast();
	}
}
