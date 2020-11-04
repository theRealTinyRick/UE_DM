// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class DM_API ACardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* CardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* CardBackMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ApproximateCardHeight = 120;

	UPROPERTY(BlueprintReadonly)
	UCard* Card;

	UPROPERTY(BlueprintReadonly)
	ADuelPawn* DuelPawnOwner;


public:	
	FORCEINLINE UCard* GetCard() { return Card; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetCard( UCard* CardToSet, ADuelPawn* NewDuelPawnOwner );

private:
	FORCEINLINE bool IsEven( int Number ) { return Number % 2 == 0; }
	friend class ADuelPawn;
};
