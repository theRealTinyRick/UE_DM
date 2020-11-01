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

	UPROPERTY(BlueprintReadonly)
	UCard* Card;

public:	
	FORCEINLINE UCard* GetCard() { return Card; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetCard( UCard* CardToSet );

private:
	friend class ADuelPawn;
};
