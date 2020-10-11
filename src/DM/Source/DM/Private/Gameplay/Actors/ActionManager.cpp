// Fill out your copyright notice in the Description page of Project Settings.


#include <Gameplay/Actors/ActionManager.h>
#include "Engine/World.h"
#include <Components/SceneComponent.h>
#include <Gameplay/GameState/DMGameState.h>

AActionManager::AActionManager()
{
	USceneComponent* NewRoot = CreateDefaultSubobject<USceneComponent>( TEXT( "Root Component" ) );
	SetRootComponent( NewRoot );
}

void AActionManager::BeginPlay()
{
	Super::BeginPlay();

	auto GameState = GetWorld()->GetGameState<ADMGameState>();
	if ( GameState != nullptr )
	{
		GameState->SpawnedActionManager = this;
	}
}

void AActionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActionManager::ActionName_Implementation( const TArray<FString>& Cards )
{
	ActionName_Execute(Cards);
}

void AActionManager::ActionName_Execute_Implementation( const TArray<FString>& Cards )
{
	/*for(FString Card : Cards)
	{
		DM_SCREENLOG( *Card, 10 );

	}*/
	/*if (IsLocallyControlled())
	{
		DM_SCREENLOG("Is Locally Controlled", 10);
	}
	else
	{
		DM_SCREENERROR("Is NOT Locally Controlled", 10);
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		DM_SCREENLOG("Is Authority", 10);
	}
	else
	{
		DM_SCREENERROR("Is NOT Authority", 10);
	}*/
}

