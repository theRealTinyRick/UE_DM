// Fill out your copyright notice in the Description page of Project Settings.


#include <Framework/Card/Card.h>

UCard::UCard()
{
	PreviousLocation = ECardLocation::NONE;
	CurrentLocation = ECardLocation::NONE;
}

UCard::~UCard()
{
}

void UCard::Initialize( UCardIdentity* CardIdentity, UDuelist* NewOwner )
{
	if ( CardIdentity == nullptr )
	{
		DM_ERROR( "[UCard]: Cannot initialize UCard with a null Card Identity" )
		return;
	}

	if (NewOwner == nullptr)
	{
		DM_ERROR("[UCard]: Cannot initialize UCard with a null Owner")
		return;
	}

	CardId = CardIdentity;

	Owner = NewOwner;
	CardName = CardIdentity->GetCardName();
	Civilizations = CardIdentity->GetCivilizations();
	CardType = CardIdentity->GetCardType();
	ManaCost = CardIdentity->GetManaCost();
	Races = CardIdentity->GetRaces();
	Power = CardIdentity->GetPower();
	bIsBlocker = CardIdentity->GetIsBlocker();
	bIsShieldTrigger = CardIdentity->GetIsShieldTrigger();
	Effects = CardIdentity->GetEffects();
	SpellEffects = CardIdentity->GetSpellEffects();

	bIsInitialized = true;
}

void UCard::ResetCard()
{
	Owner = Owner;
	CardName = CardName;
	Civilizations = Civilizations;
	CardType = CardType;
	Races = Races;
	Power = Power;
	bIsBlocker = bIsBlocker;
	bIsShieldTrigger = bIsShieldTrigger;
	Effects = Effects;
	SpellEffects = SpellEffects;
}
