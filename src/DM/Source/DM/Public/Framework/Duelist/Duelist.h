// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Framework/Card/CardLocation.h>
#include "Duelist.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class DM_API UDuelist : public UObject
{
	GENERATED_BODY()

public:
	UDuelist();
	~UDuelist();

protected:
	UPROPERTY(BlueprintReadOnly)
	int PlayerNumber = -1;
	
	UPROPERTY( BlueprintReadOnly )
	TMap<TEnumAsByte<ECardLocation>, UCardCollection*> CardCollections;

public:
	UFUNCTION(BlueprintCallable)
	UCardCollection* GetCollection(TEnumAsByte<ECardLocation> Location);

	UFUNCTION(BlueprintCallable)
	void SetDeck(TArray<UCardIdentity*> DeckIdentity);

private:
	friend class ADuelPawn;
	
};
