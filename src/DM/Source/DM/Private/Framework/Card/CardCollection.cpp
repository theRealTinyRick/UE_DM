// Fill out your copyright notice in the Description page of Project Settings.


#include <Framework/Card/CardCollection.h>

bool UCardCollection::AddCard(UCard* NewCard)
{
	if (NewCard != nullptr)
	{
		if (Contains(NewCard))
		{
			Cards.Add((NewCard));
			CardAddedEvent.Broadcast(NewCard);
			return true;
		}
	}
	return false;
}

bool UCardCollection::Remove(UCard* NewCard)
{
	if (NewCard != nullptr)
	{
		if (Contains(NewCard))
		{
			Cards.Remove(NewCard);
			CardRemovedEvent.Broadcast(NewCard);
			return true;
		}
	}
	return false;
}

bool UCardCollection::Empty()
{
	if (Cards.Num() > 0)
	{
		Cards.Empty();
		return true;
	}
	return false;
}
