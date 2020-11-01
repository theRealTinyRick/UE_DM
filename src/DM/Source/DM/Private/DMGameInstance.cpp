/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#include "DMGameInstance.h"
#include <Core/NetworkManager.h>
#include <Framework/Deck.h>


UDMGameInstance::UDMGameInstance()
{
	if(DeckClass == nullptr)
	{
		DeckClass = UDeck::StaticClass();
	}
}

void UDMGameInstance::Init()
{
	Super::Init();

	// instantiate manager objects. 
	NetworkManager = UNetworkManager::GetNetworkManagerInstance();
	if ( NetworkManager != nullptr )
	{
		NetworkManager->Init( this );
	}

	PlayerChosenDeck = NEW_OBJECT( UDeck, DeckClass );
}