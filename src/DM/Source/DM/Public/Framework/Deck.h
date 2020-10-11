// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Deck.generated.h"

class UCardIdentity;

/**
 * 
 */
UCLASS( BlueprintType, Blueprintable )
class DM_API UDeck : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UCardIdentity*> Deck;

public:
	UFUNCTION(BlueprintCallable)
	void Add(UCardIdentity* NewCard);

	UFUNCTION(BlueprintCallable)
	void Remove(UCardIdentity* TargetCard);

	UFUNCTION(BlueprintCallable)
	void RemoveAll(UCardIdentity* TargetCard);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UCardIdentity*> GetDeck() { return Deck; }

};
