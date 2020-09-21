/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DMGameInstance.generated.h"

class UNetworkManager;

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
	UPROPERTY()
	UNetworkManager* NetworkManager;

protected:
	virtual void Init() override;

public:
	UFUNCTION( BlueprintCallable )
	UNetworkManager* GetNetworkManager() { return NetworkManager; }

};
