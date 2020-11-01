// Fill out your copyright notice in the Description page of Project Settings.


#include <Framework/Duelist/Duelist.h>
#include <Framework/Card/CardCollection.h>
#include <Framework/Card/CardIdentity.h>
#include <Framework/Card/Card.h>

#define NEW_COLLECTION NEW_OBJECT(UCardCollection, UCardCollection::StaticClass())
#define NEW_CARD NEW_OBJECT(UCard, UCard::StaticClass())

UDuelist::UDuelist()
{
	CardCollections = TMap<TEnumAsByte<ECardLocation>, UCardCollection*>
	{
		{ECardLocation::DECK, NEW_COLLECTION},
		{ECardLocation::HAND, NEW_COLLECTION},
		{ECardLocation::BATTLEZONE, NEW_COLLECTION},
		{ECardLocation::SHIELDZONE, NEW_COLLECTION},
		{ECardLocation::MANAZONE, NEW_COLLECTION},
		{ECardLocation::GRAVEYARD, NEW_COLLECTION},
		{ECardLocation::REMOVEDFROMGAME, NEW_COLLECTION}
	};
}


UDuelist::~UDuelist()
{
}


UCardCollection* UDuelist::GetCollection(TEnumAsByte<ECardLocation> Location)
{
	if (CardCollections.Contains(Location))
	{
		return CardCollections[Location];
	}

	return nullptr;
}


void UDuelist::SetDeck(TArray<UCardIdentity*> DeckIdentity)
{
	UCardCollection* Deck = GetCollection(ECardLocation::DECK);
	Deck->Empty();

	for (UCardIdentity* CardId : DeckIdentity)
	{
		UCard* NewCard = NEW_CARD;
		NewCard->Initialize(CardId, this);
		Deck->AddCard(NewCard);

		//DM_SCREENLOG( FString::Printf( TEXT( "New Card Created: %s" ), *NewCard->GetCardName() ), 10 );
	}
	CardCollections[ECardLocation::DECK] = Deck;
}
