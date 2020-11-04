// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DM/DMGameModeBase.h"
#include "DuelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DM_API ADuelGameMode : public ADMGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void SetupGame() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameSetup();
};
