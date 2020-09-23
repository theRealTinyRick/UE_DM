/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Race.generated.h"

/**
 *  DataAsset representing a creature race.
 */
UCLASS( BlueprintType )
class DM_API URace : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FString RaceName;

public:
	FORCEINLINE FString GetRaceName() { return RaceName; }

};
