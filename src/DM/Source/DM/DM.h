/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
* @Description: Contains common headers and macros used across the project. 
*/

#pragma once

#include "CoreMinimal.h"

#include "Engine.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#include <Framework/Card/Race/Race.h>
#include <Framework/Card/Card.h>
#include <Framework/Card/CardCollection.h>
#include <Framework/Card/CardIdentity.h>
#include <Framework/Card/CardLocation.h>
#include <Framework/Card/Effect/EffectAction.h>
#include <Framework/Card/Effect/EffectTrigger.h>
#include <Framework/Duelist/Duelist.h>
#include <Framework/Deck.h>

#pragma region LOG_MACROS
#define DM_LOG_TAG "[DuelMasters]:"

DECLARE_LOG_CATEGORY_EXTERN( DuelMastersLog, Log, All );

#define DM_LOG(x) UE_LOG(DuelMastersLog, Log, TEXT("[DuelMasters]: %s"), *FString(x) );
#define DM_WARNING(x) UE_LOG(DuelMastersLog, Warning, TEXT("[DuelMasters]: %s"), *FString(x) );
#define DM_ERROR(x) UE_LOG(DuelMastersLog, Error, TEXT("[DuelMasters]: %s"), *FString(x) );

#define DM_SCREENLOG(x, t) GEngine->AddOnScreenDebugMessage( -1, t, FColor::Blue, FString::Printf( TEXT( "[DuelMasters]: %s" ), *FString(x)) );
#define DM_SCREENWARNING(x, t) GEngine->AddOnScreenDebugMessage( -1, t, FColor::Yellow, FString::Printf( TEXT( "[DuelMasters]: %s" ), *FString(x) ) );
#define DM_SCREENERROR(x, t) GEngine->AddOnScreenDebugMessage( -1, t, FColor::Red, FString::Printf( TEXT( "[DuelMasters]: %s" ), *FString(x) ) );
#pragma endregion


#pragma region CONSTANTS
#define NUMBER_OF_PLAYERS 2
#define REMOTE_TAG "Remote"
#define LOCAL_TAG "Local"
#define CARD_TAG "Card"
#pragma endregion


#pragma region OBJECTS
#define NEW_OBJECT(T, C) NewObject<T>( (UObject*)GetTransientPackage(), C )
#pragma endregion

//Will exit the function if no target player can be found
#define ACTION_EXECUTE LocatePlayerPawns();\
					   ADuelPawn* TargetPawn = GetPlayerByNumber( TargetPlayerNumber );\
					   if ( TargetPawn == nullptr )\
					   {\
					       return;\
					   }\
					   if(TargetPawn->GetDuelist() == nullptr)\
					   {\
						   return;\
					   }