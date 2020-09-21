/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#include <Core/NetworkManager.h>
#include <DMGameInstance.h>


#define SESSION_NAME "TestSession"
#define SERVER_NAME_SETTINGS_KEY TEXT( "ServerName" )

#pragma region STATIC_IMPLEMENTATIONS
UNetworkManager* UNetworkManager::NetworkManagerInstance = nullptr;
#pragma endregion


UNetworkManager::UNetworkManager()
{
	if ( NetworkManagerInstance != nullptr )
	{
		DM_ERROR( "[UNetworkManager]: You are creating an instance of the Network Manager while one already exists." );
	}
}


UNetworkManager::~UNetworkManager()
{
	if ( NetworkManagerInstance == this )
	{
		NetworkManagerInstance = nullptr;
	}
}


void UNetworkManager::Init( UDMGameInstance* NewGameInstance )
{
	if ( NewGameInstance == nullptr )
	{
		DM_WARNING( "Cannot Init() with a null GameInstance." );
		return;
	}

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if ( Subsystem != nullptr )
	{
		CurrentSessionInterface = Subsystem->GetSessionInterface();
		if ( CurrentSessionInterface.IsValid() )
		{
			// setup callbacks
			CurrentSessionInterface->OnCreateSessionCompleteDelegates.AddUObject( this, &UNetworkManager::OnSessionCreated );
			CurrentSessionInterface->OnCreateSessionCompleteDelegates.AddUObject( this, &UNetworkManager::OnSessionDestroyed );
			CurrentSessionInterface->OnFindSessionsCompleteDelegates.AddUObject( this, &UNetworkManager::OnSessionFound );
			CurrentSessionInterface->OnJoinSessionCompleteDelegates.AddUObject( this, &UNetworkManager::OnJoinSessionComplete );
		}
	}
}


void UNetworkManager::Host( bool IsPrivate )
{
	if ( CurrentSessionInterface.IsValid() )
	{
		FNamedOnlineSession* SessionToDestroy = CurrentSessionInterface->GetNamedSession( FName( SESSION_NAME ) );
		if ( SessionToDestroy != nullptr && SessionToDestroy->bHosting )
		{
			CurrentSessionInterface->DestroySession( SESSION_NAME );
		}
		else
		{
			CreateSession( SESSION_NAME, IsPrivate );
		}
	}
}


void UNetworkManager::CreateSession( FString ServerName, bool IsPrivate )
{
	if ( CurrentSessionInterface.IsValid() )
	{
		FOnlineSessionSettings Settings;
		Settings.bIsLANMatch = true;
		Settings.NumPublicConnections = NUMBER_OF_PLAYERS;
		Settings.bShouldAdvertise = !IsPrivate;
		Settings.Set( SERVER_NAME_SETTINGS_KEY, ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing );

		CurrentSessionInterface->CreateSession( 0, *ServerName, Settings );
	}
}


void UNetworkManager::FindSessions()
{
}


void UNetworkManager::JoinSession( uint32 Index )
{
}


void UNetworkManager::OnSessionCreated( FName SessionName, bool Success )
{
	if ( Success )
	{
		StartedHostingEvent.Broadcast();
	}
	else
	{
		DM_ERROR( "[UNetworkManager]: Cannot host. Session failed to be created." );
	}
}


void UNetworkManager::OnSessionDestroyed( FName SessionName, bool Success )
{
}


void UNetworkManager::OnSessionFound( bool Success )
{
}


void UNetworkManager::OnJoinSessionComplete( FName SessionName, EOnJoinSessionCompleteResult::Type Result )
{
}


UNetworkManager* UNetworkManager::GetNetworkManagerInstance()
{
	if ( NetworkManagerInstance == nullptr )
	{
		NetworkManagerInstance = NewObject<UNetworkManager>( (UObject*)GetTransientPackage(), UNetworkManager::StaticClass() );
	}

	return NetworkManagerInstance;
}