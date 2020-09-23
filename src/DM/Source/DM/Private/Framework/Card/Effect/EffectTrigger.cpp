// Fill out your copyright notice in the Description page of Project Settings.


#include <Framework\Card\Effect\EffectTrigger.h>


void UEffectTrigger::InitializeTrigger( UCard* NewOwningCard )
{
	OwningCard = NewOwningCard;
	PostInitializeTrigger();
}
