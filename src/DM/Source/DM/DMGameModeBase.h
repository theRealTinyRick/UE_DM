// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DMGameModeBase.generated.h"

class AActionManager;
class ADuelPawn;

/**
 * 
 */
UCLASS()
class DM_API ADMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	AActionManager* SpawnedActionManager;
	
	UPROPERTY(BlueprintReadOnly)
	ADuelPawn* PlayerOne;
	
	UPROPERTY(BlueprintReadOnly)
	ADuelPawn* PlayerTwo;


protected:
	UFUNCTION(BlueprintCallable, Category="Game Start")
	virtual void HandlePlayerStart( APlayerController* PlayerController );
	
	UFUNCTION(BlueprintCallable, Category="Game Start")
	virtual void SpawnActionManager(APlayerController* NewOwner);
	
	UFUNCTION()
	void StartGame();	

	UFUNCTION(BlueprintImplementableEvent)
	void PostStartGame();

public:
	FORCEINLINE AActionManager* GetActionManager() { return SpawnedActionManager; }

};
