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

protected:
	UPROPERTY()
	UDuelist* Owner;
	
	UPROPERTY()
	FString CardName;
	
	UPROPERTY()
	TArray<TEnumAsByte<ECivilization>> Civilizations;
	
	UPROPERTY()
	TEnumAsByte<ECardType> CardType;
	
	UPROPERTY()
	TArray<URace*> Races;
	
	UPROPERTY()
	TArray<FEffect> Effects;
	
	UPROPERTY()
	TArray<TSubclassOf<UEffectAction>> SpellEffects;
	
	UPROPERTY()
	UMaterial* CardMaterial;

	int ManaCost;
	int Power;
	bool bIsBlocker;
	bool bIsShieldTrigger;

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
	
	bool bIsInitialized = false;

public:
	void Initialize( UCardIdentity* CardIdentity, UDuelist* NewOwner);
	
	UFUNCTION( BlueprintCallable )
	void ResetCard();

public:
	FORCEINLINE UDuelist* GetCardOwner() { return OverrideOwner; }
	FORCEINLINE FString GetCardName() { return OverrideCardName; }
	FORCEINLINE TArray<TEnumAsByte<ECivilization>> GetCivilizations() { return OverrideCivilizations; }
	FORCEINLINE TEnumAsByte<ECardType> GetCardType() { return OverrideCardType; }
	FORCEINLINE int GetManaCost() { return OverrideManaCost; }
	FORCEINLINE TArray<URace*> GetRaces() { return OverrideRaces; }
	FORCEINLINE int GetPower() { return OverridePower; }
	FORCEINLINE bool GetIsBlocker() { return bOverrideIsBlocker; }
	FORCEINLINE bool GetIsShieldTrigger() { return bOverrideIsShieldTrigger; }
	FORCEINLINE TArray<FEffect> GetEffects() { return OverrideEffects; }
	FORCEINLINE TArray<TSubclassOf<UEffectAction>> GetSpellEffects() { return OverrideSpellEffects; }
	FORCEINLINE UMaterial* GetCardMaterial() { return CardMaterial; }
	FORCEINLINE bool GetIsInitialized() { return bIsInitialized; }

};
