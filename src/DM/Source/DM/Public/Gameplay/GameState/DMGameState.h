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
	UPROPERTY(BlueprintReadOnly)
	bool bIsServer = false;

#pragma region RPCs
#pragma endregion
};
