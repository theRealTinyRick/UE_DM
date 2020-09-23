/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/


#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectTrigger.generated.h"

class UCard;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DM_API UEffectTrigger : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	UCard* OwningCard;

public:
	void InitializeTrigger( UCard* NewOwningCard );

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PostInitializeTrigger();
	
};
