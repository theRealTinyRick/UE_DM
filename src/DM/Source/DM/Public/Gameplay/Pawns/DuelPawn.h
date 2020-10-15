// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DuelPawn.generated.h"

class ADMGameState;

UCLASS()
class DM_API ADuelPawn : public APawn
{
	GENERATED_BODY()

public:
	ADuelPawn();

public:
	UPROPERTY(BlueprintReadOnly)
	int PlayerNumber = 0;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
