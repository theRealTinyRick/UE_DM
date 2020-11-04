// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DuelPawn.generated.h"

class AActionManager;
class ACardActor;
class USceneComponent;

UCLASS()
class DM_API ADuelPawn : public APawn
{
	GENERATED_BODY()

public:
	ADuelPawn();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* MyRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* DeckLocator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* HandLocator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* GraveyardLocator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* BattleZoneLocator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* ShieldZoneLocator;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* ManaZoneLocator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ACardActor> CardClass;

	UPROPERTY(BlueprintReadOnly)
	int PlayerNumber = -1;

	UPROPERTY()
	bool bIsPlayerNumberSet = false;

	UPROPERTY()
	AActionManager* ActionManager;

	UPROPERTY()
	UDuelist* Duelist;

	UPROPERTY()
	UDeck* Deck;


public:
	void SetPlayerNumber( int NewPlayerNumber );

#pragma region GETTERS
	FORCEINLINE UDuelist* GetDuelist() { return Duelist; }
	FORCEINLINE int GetPlayerNumber() { return PlayerNumber; }
	FORCEINLINE bool GetIsPlayerNumberSet() { return bIsPlayerNumberSet; }
	FORCEINLINE USceneComponent* GetDeckLocator() { return DeckLocator; }
	FORCEINLINE USceneComponent* GetHandLocator() { return HandLocator; }
	FORCEINLINE USceneComponent* GetGraveyardLocator() { return GraveyardLocator; }
	FORCEINLINE USceneComponent* GetBattleZoneLocator() { return BattleZoneLocator; }
	FORCEINLINE USceneComponent* GetShieldZoneLocator() { return ShieldZoneLocator; }
	FORCEINLINE USceneComponent* GetManaZoneLocator() { return ManaZoneLocator; }

#pragma endregion GETTERS


protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
	
	virtual void FindActionManager();

	UFUNCTION()
	void OnCardShouldSpawn(UCard* TargetCard, UDuelist* TargetDuelist);

private: 
	friend class AActionManager;

};
