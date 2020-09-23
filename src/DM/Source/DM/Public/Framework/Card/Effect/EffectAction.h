/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectAction.generated.h"

class UCard;
class UEffectTrigger;

/**
 * 
 */
UCLASS( BlueprintType, Blueprintable )
class DM_API UEffectAction : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY( BlueprintReadOnly )
	UCard* OwningCard;

public:
	void InitializeEffect( UCard* NewOwningCard );

protected:
	UFUNCTION( BlueprintImplementableEvent )
	void PostInitializeEffect();
	
	UFUNCTION( BlueprintImplementableEvent )
	void ExecuteEffect(UEffectTrigger* Trigger);
};
