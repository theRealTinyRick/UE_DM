// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardCollection.generated.h"

class UCard;
class UCardIdentity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FCardCollectionDelegateNone );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FCardCollectionDelegate, UCard*, Card );

USTRUCT( BlueprintType )
struct FCardCollection
{
	GENERATED_USTRUCT_BODY()
	FCardCollection() {}
	FCardCollection( TArray<UCardIdentity*> CardIdentities /**/ )
	{

	}

	UPROPERTY( BlueprintAssignable )
	FCardCollectionDelegate CardAddedEvent;

	UPROPERTY( BlueprintAssignable )
	FCardCollectionDelegate CardRemovedEvent;

	UPROPERTY( BlueprintAssignable )
	FCardCollectionDelegateNone CollectionInitializedEvent;

protected:
	UPROPERTY( BlueprintReadOnly )
	TArray<UCard*> Cards;

public:
	bool AddCard( UCard* NewCard )
	{
		if ( NewCard != nullptr )
		{
			if ( Contains( NewCard ) )
			{
				Cards.Add( (NewCard) );
				CardAddedEvent.Broadcast( NewCard );
				return true;
			}
		}
		return false;
	}

	bool Remove( UCard* NewCard )
	{
		if ( NewCard != nullptr )
		{
			if ( Contains( NewCard ) )
			{
				Cards.Remove( NewCard );
				CardRemovedEvent.Broadcast( NewCard );
				return true;
			}
		}
		return false;
	}

	bool Empty()
	{
		if ( Cards.Num() > 0 )
		{
			Cards.Empty();
			return true;
		}
		return false;
	}

	FORCEINLINE bool Contains( UCard* NewCard ) { return NewCard != nullptr && Cards.Contains( NewCard ); }
	FORCEINLINE TArray<UCard*> GetCards() { return Cards; }


};
