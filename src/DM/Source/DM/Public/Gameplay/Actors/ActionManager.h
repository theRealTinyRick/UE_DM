// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Gameplay/Pawns/DuelPawn.h>
#include "ActionManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FActionCardDelegate, UCard*, Card, UDuelist*, Owner );

UCLASS()
class DM_API AActionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AActionManager();

public:
	UPROPERTY( BlueprintAssignable )
	FActionCardDelegate ShieldAddedEvent;
	
	UPROPERTY( BlueprintAssignable )
	FActionCardDelegate CardDrawnEvent;
	
	UPROPERTY( BlueprintAssignable )
	FActionCardDelegate LastCardDrawnEvent;
	
protected:
	ADuelPawn* PlayerOne;
	
	UPROPERTY()
	ADuelPawn* PlayerTwo;
	
#pragma region RPC EXAMPLE
	UFUNCTION( BlueprintCallable, Server, Reliable )
	void ActionName(const TArray<FString>& Cards);

	UFUNCTION( NetMulticast, Reliable )
	void ActionName_Execute( const TArray<FString>& Cards );
#pragma endregion

public:
	void LocatePlayerPawns();
	ADuelPawn* GetPlayerByNumber( int Number );

#pragma region RPCS
	//Shields
	UFUNCTION( BlueprintCallable, Server, Reliable )
	void AddShield( int TargetPlayerNumber, int AmountToAdd = 1 );
	
	UFUNCTION( NetMulticast, Reliable )
	void AddShield_Execute( int TargetPlayerNumber, int AmountToAdd = 1 );
	

	// Drawing
	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Draw( int TargetPlayerNumber, int AmountToDraw = 1);

	UFUNCTION( NetMulticast, Reliable )
	void Draw_Execute( int TargetPlayerNumber, int AmountToDraw = 1 );
#pragma endregion

#pragma region GETTERS
	FORCEINLINE ADuelPawn* GetPlayerOne() { return PlayerOne; }
	FORCEINLINE ADuelPawn* GetPlayerTwo() { return PlayerTwo; }


	FORCEINLINE UDuelist* GetDuelistOne() { return PlayerOne != nullptr ? PlayerOne->GetDuelist() : nullptr; }
	FORCEINLINE UDuelist* GetDuelistTwo() { return PlayerTwo != nullptr ? PlayerTwo->GetDuelist() : nullptr; }
	
	FORCEINLINE ADuelPawn* GetPlayer( int Number ) { return Number == 1 ? PlayerOne : Number == 2 ? PlayerTwo : nullptr; }
	FORCEINLINE UDuelist* GetDuelist( int Number ) { return Number == 1 ? GetDuelistOne() : Number == 2 ? GetDuelistTwo(): nullptr; }

#pragma endregion GETTERS

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
};
