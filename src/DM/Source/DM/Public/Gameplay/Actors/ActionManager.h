// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionManager.generated.h"

UCLASS()
class DM_API AActionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AActionManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma region RPCS
public:
	UFUNCTION( BlueprintCallable, Server, Reliable )
	void ActionName(const TArray<FString>& Cards);

	UFUNCTION( NetMulticast, Reliable )
	void ActionName_Execute( const TArray<FString>& Cards );
#pragma endregion

};
