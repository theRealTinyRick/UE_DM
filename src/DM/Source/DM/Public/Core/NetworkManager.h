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
    FNetworkDelegateNoArgs FailedToFindSessionsEvent;
    
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
    UFUNCTION(BlueprintPure)
    static UNetworkManager* GetNetworkManagerInstance();

    FORCEINLINE bool GetHasInitialized() { return bHasInitialized; }
};
