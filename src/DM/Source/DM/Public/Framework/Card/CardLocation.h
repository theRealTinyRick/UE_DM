// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardLocation.generated.h"

UENUM(BlueprintType)
enum ECardLocation 
{
	NONE,
	DECK,
	HAND,
	BATTLEZONE,
	SHIELDZONE,
	MANAZONE,
	GRAVEYARD,
	REMOVEDFROMGAME
};