/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#include "DMGameInstance.h"
#include <Core/NetworkManager.h>


UDMGameInstance::UDMGameInstance()
{
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
}