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
	if ( CurrentSessionInterface.IsValid() )
	{
		SessionSearch = MakeShareable( new FOnlineSessionSearch() );
		if ( SessionSearch.IsValid() )
		{
			UE_LOG( LogTemp, Warning, TEXT( "Searching for sessions" ) );
			CurrentSessionInterface->FindSessions( 0, SessionSearch.ToSharedRef() );
		}
	}
}


void UNetworkManager::JoinSession( uint32 Index )
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
		DM_LOG( "Cannot Join a session of an invalid index." )
			return;
	}

	FOnlineSessionSearchResult SessionToJoin = SessionSearch->SearchResults[Index];

	CurrentSessionInterface->JoinSession( 0, SESSION_NAME, SessionToJoin );
	DM_LOG( "Join session started" );
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
	if ( Success )
	{
		CreateSession( SESSION_NAME );
		UE_LOG( LogTemp, Warning, TEXT( "Session Destroyed Sucessfully" ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Session Failed To Be Destroyed" ) );
	}
}


void UNetworkManager::OnSessionFound( bool Success )
{
	if ( Success )
	{
		TArray<FOnlineSessionSearchResult> FoundSessions = SessionSearch->SearchResults;
		if ( FoundSessions.Num() > 0 )
		{
			UE_LOG( LogTemp, Warning, TEXT( "Sessions Found" ) );
			for ( const FOnlineSessionSearchResult& FoundSession : FoundSessions )
			{
				UE_LOG( LogTemp, Warning, TEXT( "Session Found: %s" ), *FoundSession.GetSessionIdStr() );
				UE_LOG( LogTemp, Warning, TEXT( "Session Ping: %i Milliseconds" ), FoundSession.PingInMs );
			}

			JoinSession( 0 );
		}
		else
		{
			UE_LOG( LogTemp, Warning, TEXT( "Sessions Not Found" ) );
		}
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Sessions Not Found" ) );
		// start an offline game. 
	}
}


void UNetworkManager::OnJoinSessionComplete( FName SessionName, EOnJoinSessionCompleteResult::Type Result )
{
	if ( !CurrentSessionInterface.IsValid() )
	{
		return;
	}

	FString Address;
	if ( !CurrentSessionInterface->GetResolvedConnectString( SessionName, Address ) ) {
		UE_LOG( LogTemp, Warning, TEXT( "Could not get connect string." ) );
		return;
	}

	//APlayerController* PlayerController = GetFirstLocalPlayerController();
	//if ( !ensure( PlayerController != nullptr ) )
	//{
	//	return;
	//}

	//PlayerController->ClientTravel( Address, ETravelType::TRAVEL_Absolute );
	//LOG( "Join session complete" );
}


UNetworkManager* UNetworkManager::GetNetworkManagerInstance()
{
	if ( NetworkManagerInstance == nullptr )
	{
		NetworkManagerInstance = NewObject<UNetworkManager>( (UObject*)GetTransientPackage(), UNetworkManager::StaticClass() );
	}

	return NetworkManagerInstance;
}