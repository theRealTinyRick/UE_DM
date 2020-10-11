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

#pragma region LOG_MACROS
DECLARE_LOG_CATEGORY_EXTERN( DuelMastersLog, Log, All );

#define DM_LOG(x) UE_LOG(DuelMastersLog, Log, TEXT("%s"), *FString(x) );
#define DM_WARNING(x) UE_LOG(DuelMastersLog, Warning, TEXT("%s"), *FString(x) );
#define DM_ERROR(x) UE_LOG(DuelMastersLog, Error, TEXT("%s"), *FString(x) );

#define DM_SCREENLOG(x, t) GEngine->AddOnScreenDebugMessage( -1, t, FColor::Blue, FString::Printf( TEXT( "%s" ), *FString(x)) );
#define DM_SCREENWARNING(x, t) GEngine->AddOnScreenDebugMessage( -1, t, FColor::Yellow, FString::Printf( TEXT( "%s" ), *FString(x) ) );
#define DM_SCREENERROR(x, t) GEngine->AddOnScreenDebugMessage( -1, t, FColor::Red, FString::Printf( TEXT( "%s" ), *FString(x) ) );
#pragma endregion

#pragma region CONSTANTS
#define NUMBER_OF_PLAYERS 2
#define REMOTE_TAG "Remote"
#define LOCAL_TAG "Local"
#pragma endregion

#pragma region OBJECTS
#define NEW_OBJECT(T, C) NewObject<T>( (UObject*)GetTransientPackage(), C )
#pragma endregion

