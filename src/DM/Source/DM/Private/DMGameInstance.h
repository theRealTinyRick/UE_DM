/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DMGameInstance.generated.h"

class UNetworkManager;
class UDeck;

/**
 * Main game instance for the game.
 */
UCLASS()
class UDMGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDMGameInstance();

protected:
	UPROPERTY( EditAnywhere )
	TSubclassOf<UDeck> DeckClass;

protected:
	UPROPERTY()
	UNetworkManager* NetworkManager;


protected:
	virtual void Init() override;

public:
	UPROPERTY()
	UDeck* PlayerChosenDeck;

	UFUNCTION( BlueprintCallable )
	UNetworkManager* GetNetworkManager() { return NetworkManager; }

};
