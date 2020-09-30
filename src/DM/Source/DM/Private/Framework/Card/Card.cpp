// Fill out your copyright notice in the Description page of Project Settings.


#include <Framework/Card/Card.h>

UCard::UCard()
{
}

UCard::~UCard()
{
}

void UCard::Initialize( UCardIdentity* CardIdentity, UDuelist* NewOwner)
{
	if (Owner == nullptr)
	{
		DM_ERROR("[UCard]: Cannot initialize UCard with a null Owner")
		return;
	}

	Owner = NewOwner;
	OverrideOwner = Owner;

	CardName = CardIdentity->GetCardName();
	OverrideCardName = CardName;

	Civilizations = CardIdentity->GetCivilizations();
	OverrideCivilizations = Civilizations;

	CardType = CardIdentity->GetCardType();
	OverrideCardType = CardType;

	ManaCost = CardIdentity->GetManaCost();
	OverrideManaCost = ManaCost;

	Races = CardIdentity->GetRaces();
	OverrideRaces = Races;

	Power = CardIdentity->GetPower();
	OverridePower = Power;

	bIsBlocker = CardIdentity->GetIsBlocker();
	bOverrideIsBlocker = bIsBlocker;

	bIsShieldTrigger = CardIdentity->GetIsShieldTrigger();
	bOverrideIsShieldTrigger = bIsShieldTrigger;

	Effects = CardIdentity->GetEffects();
	OverrideEffects = Effects;

	SpellEffects = CardIdentity->GetSpellEffects();
	OverrideSpellEffects = SpellEffects;

	bIsInitialized = true;
}

void UCard::ResetCard()
{
	OverrideOwner = Owner;
	OverrideCardName = CardName;
	OverrideCivilizations = Civilizations;
	OverrideCardType = CardType;
	OverrideRaces = Races;
	OverridePower = Power;
	bOverrideIsBlocker = bIsBlocker;
	bOverrideIsShieldTrigger = bIsShieldTrigger;
	OverrideEffects = Effects;
	OverrideSpellEffects = SpellEffects;
}
