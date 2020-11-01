// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardCollection.generated.h"

class UCard;
class UCardIdentity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCardCollectionDelegateNone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardCollectionDelegate, UCard*, Card);

/**
 * 
 */
UCLASS(BlueprintType)
class DM_API UCardCollection : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCardCollectionDelegate CardAddedEvent;

	UPROPERTY(BlueprintAssignable)
	FCardCollectionDelegate CardRemovedEvent;

	UPROPERTY(BlueprintAssignable)
	FCardCollectionDelegateNone CollectionInitializedEvent;

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<UCard*> Cards;

public:
	bool AddCard(UCard* NewCard);
	bool RemoveCard(UCard* NewCard);
	bool Empty();

	FORCEINLINE bool Contains(UCard* NewCard) { return NewCard != nullptr && Cards.Contains(NewCard); }
	FORCEINLINE TArray<UCard*> GetCards() { return Cards; }


};
