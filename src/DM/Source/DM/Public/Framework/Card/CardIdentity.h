/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
* @Description: 
*/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Effect/Effect.h"

#include "CardIdentity.generated.h"

class URace;
class UMaterial;

UENUM( BlueprintType )
enum ECivilization
{
	LIGHT,
	WATER,
	DARKNESS,
	FIRE,
	NATURE
};

UENUM( BlueprintType )
enum ECardType
{
	CREATURE,
	SPELL
};

/**
 * Data Asset Representing a card. Not an instance of one. 
 */
UCLASS(BlueprintType)
class DM_API UCardIdentity : public UDataAsset
{
	GENERATED_BODY()
public:
	UCardIdentity();
	~UCardIdentity();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FString CardName;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	UMaterial* CardMaterial;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray<TEnumAsByte<ECivilization>> Civilizations;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TEnumAsByte<ECardType> CardType;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	int ManaCost = 1;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "CardType==ECardType::Creature") )
	TArray<URace*> Races;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "CardType==ECardType::Creature") )
	int Power;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "CardType==ECardType::Creature") )
	int NumberOfShieldsToBreak = 1;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "CardType==ECardType::Creature") )
	bool bIsBlocker;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	bool bIsShieldTrigger;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "CardType==ECardType::Creature") )
	TArray<FEffect> Effects;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "CardType==ECardType::Spell") )
	TArray<TSubclassOf<UEffectAction>> SpellEffects;

public:
	//TODO: Add all getters 
	FORCEINLINE FString GetCardName() { return CardName; }
	FORCEINLINE TArray<TEnumAsByte<ECivilization>> GetCivilizations() { return Civilizations; }
	FORCEINLINE TArray<URace*> GetRaces() { return Races; }
	FORCEINLINE TEnumAsByte<ECardType> GetCardType() { return CardType; }
	FORCEINLINE int GetManaCost() { return ManaCost; }
	FORCEINLINE int GetPower() { return Power; }
	FORCEINLINE bool GetIsBlocker() { return bIsBlocker; }
	FORCEINLINE bool GetIsShieldTrigger() { return bIsShieldTrigger; }
	FORCEINLINE TArray<FEffect> GetEffects() { return Effects; }
	FORCEINLINE TArray<TSubclassOf<UEffectAction>> GetSpellEffects() { return SpellEffects; }

};
