// Fill out your copyright notice in the Description page of Project Settings.


#include <Framework\Deck.h>
#include <Framework\Card\CardIdentity.h>


TArray<FString> UDeck::GetDeckData()
{
	TArray<FString> Data = TArray<FString>();
	for(UCardIdentity* CardIdentity : Deck)
	{
		Data.Add( CardIdentity->GetCardName() );
	}

	return Data;
}

void UDeck::Add( UCardIdentity* NewCard )
{
}

void UDeck::Remove( UCardIdentity* TargetCard )
{
}

void UDeck::RemoveAll( UCardIdentity* TargetCard )
{
}
