// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Framework/Card/CardIdentity.h>
#include <Framework/Card/CardLocation.h>

#include "Card.generated.h"

class UTexture2D;
class UCardIdentity;
class UDuelist;

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
	UCardIdentity* CardId;

	UPROPERTY()
	UDuelist* Owner;
	
	UPROPERTY()
	TEnumAsByte<ECardLocation> CurrentLocation;
	
	UPROPERTY()
	TEnumAsByte<ECardLocation> PreviousLocation;

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
	bool bIsInitialized = false;

public:
	void Initialize( UCardIdentity* CardIdentity, UDuelist* NewOwner);
	
	UFUNCTION( BlueprintCallable )
	void ResetCard();

public:
	FORCEINLINE UDuelist* GetCardOwner() { return Owner; }
	FORCEINLINE TEnumAsByte<ECardLocation> GetCurrentLocation() { return CurrentLocation; }
	FORCEINLINE FString GetCardName() { return CardName; }
	FORCEINLINE TArray<TEnumAsByte<ECivilization>> GetCivilizations() { return Civilizations; }
	FORCEINLINE TEnumAsByte<ECardType> GetCardType() { return CardType; }
	FORCEINLINE int GetManaCost() { return ManaCost; }
	FORCEINLINE TArray<URace*> GetRaces() { return Races; }
	FORCEINLINE int GetPower() { return Power; }
	FORCEINLINE bool GetIsBlocker() { return bIsBlocker; }
	FORCEINLINE bool GetIsShieldTrigger() { return bIsShieldTrigger; }
	FORCEINLINE TArray<FEffect> GetEffects() { return Effects; }
	FORCEINLINE TArray<TSubclassOf<UEffectAction>> GetSpellEffects() { return SpellEffects; }
	FORCEINLINE UMaterial* GetCardMaterial() { return CardMaterial; }
	FORCEINLINE bool GetIsInitialized() { return bIsInitialized; }


private:
	friend class AActionManager;
};
