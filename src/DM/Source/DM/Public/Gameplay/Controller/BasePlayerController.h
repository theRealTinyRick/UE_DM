// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void ReceivedPlayer() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnReceivedPlayer();

};
