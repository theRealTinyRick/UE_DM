/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#include <Core/NetworkManager.h>
#include <DMGameInstance.h>
#include <Engine/Engine.h>
#include <Engine/World.h>


#define SESSION_NAME "TestSession"
#define SERVER_NAME_SETTINGS_KEY TEXT( "ServerName" )

const float LOG_TIME = 0;

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


bool PendingSessionCreation = false;
void UNetworkManager::Host( bool IsPrivate )
{
	if ( CurrentSessionInterface.IsValid() )
	{
		FNamedOnlineSession* SessionToDestroy = CurrentSessionInterface->GetNamedSession( FName( SESSION_NAME ) );
		if ( SessionToDestroy != nullptr )
		{
			PendingSessionCreation = true;
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
	if ( CurrentSessionInterface.IsValid() )
	{
		SessionSearch = MakeShareable( new FOnlineSessionSearch() );
		if ( SessionSearch.IsValid() )
		{
			DM_SCREENLOG( "Searching for sessions", LOG_TIME );
			SessionSearch->bIsLanQuery = true;
			CurrentSessionInterface->FindSessions( 0, SessionSearch.ToSharedRef() );
		}
	}
}


void UNetworkManager::JoinSession( int Index )
{
	if ( !CurrentSessionInterface.IsValid() )
	{
		return;
	}

	if ( !SessionSearch.IsValid() )
	{
		return;
	}

	if ( !SessionSearch->SearchResults.IsValidIndex( Index ) )
	{
		DM_SCREENLOG( "Cannot Join a session of an invalid index.", LOG_TIME );
		return;
	}

	FOnlineSessionSearchResult SessionToJoin = SessionSearch->SearchResults[Index];

	CurrentSessionInterface->JoinSession( 0, SESSION_NAME, SessionToJoin );
	DM_SCREENLOG( "Join session started", LOG_TIME );
}


void UNetworkManager::OnSessionCreated( FName SessionName, bool Success )
{
	if ( Success )
	{
		StartedHostingEvent.Broadcast();
		DM_SCREENLOG( "[UNetworkManager]: Created Session Success.", LOG_TIME );
	}
	else
	{
		DM_SCREENLOG( "[UNetworkManager]: Cannot host. Session failed to be created.", LOG_TIME );
	}
}


void UNetworkManager::OnSessionDestroyed( FName SessionName, bool Success )
{
	if ( Success )
	{
		DM_SCREENLOG( "Session Destroyed Sucessfully", LOG_TIME );
		if(PendingSessionCreation)
		{
			PendingSessionCreation = false;
			CreateSession( SESSION_NAME, false );
		}
	}
	else
	{
		DM_SCREENLOG( "Session Failed To Be Destroyed", LOG_TIME );
	}
}


void UNetworkManager::OnSessionFound( bool Success )
{
	if ( Success )
	{
		TArray<FOnlineSessionSearchResult> FoundSessions = SessionSearch->SearchResults;

		if ( FoundSessions.Num() > 0 )
		{
			SessionsFoundEvent.Broadcast();
			/*DM_SCREENLOG("Sessions Found", LOG_TIME );
			for ( const FOnlineSessionSearchResult& FoundSession : FoundSessions )
			{
				auto Message = FString::Printf( TEXT( "Session Found: %s" ), *FoundSession.GetSessionIdStr() );
				DM_SCREENLOG( Message, LOG_TIME );
				
				Message = FString::Printf( TEXT( "Session Ping: %i Milliseconds" ), FoundSession.PingInMs );
				DM_SCREENLOG( Message, LOG_TIME );
			}*/
		}
		else
		{
			DM_SCREENLOG( "Sessions Not Found, none in the array", LOG_TIME );
			FailedToFindSessionsEvent.Broadcast();
		}
	}
	else
	{
		DM_SCREENLOG( "Sessions Not Found, failed", LOG_TIME );
		// start an offline game. 
	}
}


void UNetworkManager::OnJoinSessionComplete( FName SessionName, EOnJoinSessionCompleteResult::Type Result )
{
	if ( !CurrentSessionInterface.IsValid() )
	{
		return;
	}

	DM_SCREENLOG( "Join session Completed", 10 );
	if(Result ==  EOnJoinSessionCompleteResult::Success)
	{
		DM_SCREENLOG( "Join session Completed Sucess", LOG_TIME );
	}
	else 
	{

		DM_SCREENLOG( "Join session Completed NOT Sucess", LOG_TIME );
	}


	FString Address;
	if ( !CurrentSessionInterface->GetResolvedConnectString( SessionName, Address ) ) 
	{
		DM_SCREENLOG("Could not get connect string.", LOG_TIME );
		return;
	}
	else
	{
		DM_SCREENLOG( FString("Connect String: ").Append(Address), LOG_TIME );
	}

	SessionJoinedCompleteEvent.Broadcast(Address);
}


UNetworkManager* UNetworkManager::GetNetworkManagerInstance()
{
	if ( NetworkManagerInstance == nullptr )
	{
		NetworkManagerInstance = NewObject<UNetworkManager>( (UObject*)GetTransientPackage(), UNetworkManager::StaticClass() );
	}

	return NetworkManagerInstance;
}