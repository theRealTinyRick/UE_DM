// Fill out your copyright notice in the Description page of Project Settings.


#include <Framework\Card\Effect\EffectAction.h>

void UEffectAction::InitializeEffect( UCard* NewOwningCard )
{
	OwningCard = OwningCard;
	PostInitializeEffect();
}
