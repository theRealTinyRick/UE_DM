// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/GameStateBase.h"
#include "DMGameState.generated.h"

class AActionManager;
class ADuelPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FGameStateDel );

/**
 * 
 */
UCLASS()
class DM_API ADMGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FGameStateDel GameStartedEvent;
	
	UPROPERTY(BlueprintAssignable)
	FGameStateDel GameEndedEvent;

	UPROPERTY(BlueprintReadOnly)
	bool bIsServer = false;

protected:
	FTimerHandle TimerHandle_DefaultTimer;

public:
	UPROPERTY( BlueprintReadOnly )
	AActionManager* SpawnedActionManager;

	UPROPERTY( BlueprintReadOnly )
	ADuelPawn* PlayerOne;

	UPROPERTY( BlueprintReadOnly )
	ADuelPawn* PlayerTwo;

public:
#pragma region RPCs
	UFUNCTION( Server, Reliable )
	void NotifyServerReadyToStart();
#pragma endregion

	UFUNCTION( NetMulticast, Reliable )
	void StartGame();

	UFUNCTION( NetMulticast, Reliable )
	void EndGame();
	
	void StartGame_Execute();
};
