/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"

#include <OnlineSubsystem.h>
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "UObject/NoExportTypes.h"
#include "NetworkManager.generated.h"

class UDMGameInstance;

//
//USTRUCT(BlueprintType)
//struct FOnlineSessionSearchImplementation
//{
//    GENERATED_USTRUCT_BODY()
//    FOnlineSessionSearchImplementation(){}
//    FOnlineSessionSearchImplementation( FOnlineSessionSearch SearchResult ):
//        SearchResults(SearchResult.SearchResults),
//        SearchState(SearchResult.SearchState),
//        MaxSearchResults(SearchResult.MaxSearchResults),
//        QuerySettings(SearchResult.QuerySettings),
//        bIsLanQuery(SearchResult.bIsLanQuery),
//        PingBucketSize(SearchResult.PingBucketSize),
//        PlatformHash(SearchResult.PlatformHash),
//        TimeoutInSeconds(SearchResult.TimeoutInSeconds)
//    {
//    }
//
//    /** Array of all sessions found when searching for the given criteria */
//    TArray<FOnlineSessionSearchResult> SearchResults;
//    
//    /** State of the search */
//    UPROPERTY(BlueprintReadOnly)
//    EOnlineAsyncTaskState::Type SearchState;
//    
//    /** Max number of queries returned by the matchmaking service */
//    UPROPERTY(BlueprintReadOnly)
//    int32 MaxSearchResults;
//    
//    /** The query to use for finding matching servers */
//    UPROPERTY(BlueprintReadOnly)
//    FOnlineSearchSettings QuerySettings;
//    
//    /** Whether the query is intended for LAN matches or not */
//    UPROPERTY(BlueprintReadOnly)
//    bool bIsLanQuery;
//    
//    /**
//     * Used to sort games into buckets since a the difference in terms of feel for ping
//     * in the same bucket is often not a useful comparison and skill is better
//     */
//    UPROPERTY(BlueprintReadOnly)
//    int32 PingBucketSize;
//    
//    /** Search hash used by the online subsystem to disambiguate search queries, stamped every time FindSession is called */
//    UPROPERTY(BlueprintReadOnly)
//    int32 PlatformHash;
//    
//    /** Amount of time to wait for the search results. May not apply to all platforms. */
//    UPROPERTY(BlueprintReadOnly)
//    float TimeoutInSeconds;
//};

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FNetworkDelegateNoArgs );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FNetworkDelegateStringArg, FString, String );

/**
 * Class controlling all of the network actions and callbacks. This class will reside on the gameinstance. If you want access to the correct instance get it from there. 
 */
UCLASS( BlueprintType )
class DM_API UNetworkManager : public UObject
{
	GENERATED_BODY()

public:
    UNetworkManager();
    ~UNetworkManager();

public:
    UPROPERTY( BlueprintAssignable )
    FNetworkDelegateNoArgs StartedHostingEvent;
    
    UPROPERTY( BlueprintAssignable )
    FNetworkDelegateNoArgs SessionsFoundEvent;
    
    UPROPERTY( BlueprintAssignable )
    FNetworkDelegateStringArg SessionJoinedCompleteEvent;

protected:
	UPROPERTY(BlueprintReadOnly)
    bool bHasInitialized = false;
	
    UPROPERTY()
    UDMGameInstance* GameInstance;
    
	IOnlineSessionPtr CurrentSessionInterface;
    TSharedPtr<FOnlineSessionSearch> SessionSearch;

private:
    static UNetworkManager* NetworkManagerInstance;

public:
    UFUNCTION(BlueprintCallable)
    virtual void Init( UDMGameInstance* NewGameInstance );
   
    UFUNCTION(BlueprintCallable)
    virtual void Host( bool IsPrivate = false );
   
    UFUNCTION(BlueprintCallable)
    virtual void CreateSession( FString ServerName, bool IsPrivate = false );
   
    UFUNCTION(BlueprintCallable)
    virtual void FindSessions();
   
    UFUNCTION(BlueprintCallable)
    virtual void JoinSession( int Index );
    
    virtual void OnSessionCreated( FName SessionName, bool Success );
    virtual void OnSessionDestroyed( FName SessionName, bool Success );
    virtual void OnSessionFound( bool Success );
    virtual void OnJoinSessionComplete( FName SessionName, EOnJoinSessionCompleteResult::Type Result );




public:
    UFUNCTION(BlueprintCallable)
    static UNetworkManager* GetNetworkManagerInstance();

    FORCEINLINE bool GetHasInitialized() { return bHasInitialized; }
};
