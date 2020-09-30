// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardIdentity.h"

#include "Card.generated.h"

class URace;
class UDuelist;
class UTexture2D;

/**
 * 
 */
UCLASS()
class DM_API UCard : public UObject
{
	GENERATED_BODY()
	
public:
	UCard();
	~UCard();

private:
	UDuelist* Owner;
	FString CardName;
	TArray<TEnumAsByte<ECivilization>> Civilizations;
	TEnumAsByte<ECardType> CardType;
	int ManaCost;
	TArray<URace*> Races;
	int Power;
	bool bIsBlocker;
	bool bIsShieldTrigger;
	TArray<FEffect> Effects;
	TArray<TSubclassOf<UEffectAction>> SpellEffects;
	UMaterial* CardMaterial;


protected:
	UPROPERTY( BlueprintReadOnly )
	UDuelist* OverrideOwner;

	UPROPERTY( BlueprintReadOnly )
	FString OverrideCardName;

	UPROPERTY( BlueprintReadOnly )
	TArray<TEnumAsByte<ECivilization>> OverrideCivilizations;

	UPROPERTY( BlueprintReadOnly )
	TEnumAsByte<ECardType> OverrideCardType;

	UPROPERTY( BlueprintReadOnly )
	int OverrideManaCost;

	UPROPERTY( BlueprintReadOnly )
	TArray<URace*> OverrideRaces;

	UPROPERTY( BlueprintReadOnly )
	int OverridePower;

	UPROPERTY( BlueprintReadOnly )
	bool bOverrideIsBlocker;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	bool bOverrideIsShieldTrigger;

	UPROPERTY( BlueprintReadOnly )
	TArray<FEffect> OverrideEffects;
	
	UPROPERTY( BlueprintReadOnly )
	TArray<TSubclassOf<UEffectAction>> OverrideSpellEffects;
	
	UPROPERTY( BlueprintReadOnly )
	UMaterial* OverrideCardMaterial;

	bool bIsInitialized = false;

public:
	void Initialize( UCardIdentity* CardIdentity, UDuelist* NewOwner);
	
	UFUNCTION( BlueprintCallable )
	void ResetCard();

	//TODOS: Write all the getters
};
