// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FActionManagerDelegate );

/*
* Actor intended to be spawned on the server. It will continuously send a ping to client awaiting one back.
* This way you can verify that it was spawned.
*/
UCLASS()
class DM_API APingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APingActor();

	UPROPERTY( BlueprintAssignable )
	FActionManagerDelegate FinishedPingEvent;

protected:
	bool bIsServer = false;
	bool bStartedPinging = false;
	bool bHasRecievedResponsePing = false;

protected:
	virtual void Tick(float DeltaTime) override;

#pragma region RPCS
	UFUNCTION( NetMulticast, Reliable )
	void PingClient();

	UFUNCTION( Server, Reliable )
	void PingServer();

public:
	void StartClientPing();
#pragma endregion

public: 
	bool GetHasRecievedPing() { return bHasRecievedResponsePing; }

};
