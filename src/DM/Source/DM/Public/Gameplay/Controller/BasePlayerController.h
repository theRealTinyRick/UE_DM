// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class AActionManager;
class ADuelPawn;
class ADMGameState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FPlayerControllerDel );

/**
 * 
 */
UCLASS()
class DM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

	UPROPERTY(BlueprintAssignable)
	FPlayerControllerDel ClientReadyEvent;
	
	UPROPERTY(BlueprintAssignable)
	FPlayerControllerDel GameStartEvent;

public:

protected:
	UPROPERTY(BlueprintReadOnly)
	AActionManager* ActionManager;

	UPROPERTY(BlueprintReadOnly)
	ADuelPawn* DuelPawn;

	UPROPERTY(BlueprintReadOnly)
	ADMGameState* DMGameState;

	UPROPERTY( BlueprintReadOnly )
	int PlayerNumber = -1;

	UPROPERTY(BlueprintReadOnly)
	bool bIsServer = false;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsClient = false;

	bool bHasSentServerReady = false;
	bool bShouldStartReadying = false;

protected:
	virtual void ReceivedPlayer() override;
	virtual void PlayerTick( float DeltaTime ) override;

	UFUNCTION(Server, Reliable)
	void SendClientReadyToServer();

	UFUNCTION(BlueprintImplementableEvent)
	void OnReceivedPlayer();

public:
	UFUNCTION(Client, Reliable)
	void OnGameStart();

	UFUNCTION(Client, Reliable)
	void SetIsClient();
	
	void SetIsServer();

public: 
	FORCEINLINE int GetPlayerNumber() { return PlayerNumber; }

};
