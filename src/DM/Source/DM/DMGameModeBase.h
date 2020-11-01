// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/EngineTypes.h"
#include "DMGameModeBase.generated.h"

class AActionManager;
class ADuelPawn;
class ABasePlayerController;

/**
 * Game mode that handles connected player controllers and spawning neccisary actors.
 */
UCLASS()
class DM_API ADMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GameSetupDelayTime = 0.5f;

protected:
	UPROPERTY(BlueprintReadOnly)
	AActionManager* SpawnedActionManager;
	
	UPROPERTY(BlueprintReadOnly)
	ADuelPawn* PlayerOne;
	
	UPROPERTY(BlueprintReadOnly)
	ADuelPawn* PlayerTwo;

	UPROPERTY(BlueprintReadOnly)
	ABasePlayerController* PlayerOneController;
	
	UPROPERTY(BlueprintReadOnly)
	ABasePlayerController* PlayerTwoController;

	FTimerHandle TimerHandle;

protected:
	UFUNCTION(BlueprintCallable, Category="Game Start")
	virtual void HandlePlayerStart( APlayerController* PlayerController );
	
	UFUNCTION(BlueprintCallable, Category="Game Start")
	virtual void SpawnActionManager(APlayerController* NewOwner);
	
	UFUNCTION()
	void StartGame();	
	
	UFUNCTION(BlueprintImplementableEvent)
	void PostStartGame();

	UFUNCTION()
	virtual void SetupGame();	

public:
	FORCEINLINE AActionManager* GetActionManager() { return SpawnedActionManager; }

};
