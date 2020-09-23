/*
* @Author: Aaron Hines
* @CopyRight: Aaron Hines
*/

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Effect.generated.h"

class UEffectAction;
class UEffectTrigger;

USTRUCT( BlueprintType )
struct FEffect
{
	GENERATED_USTRUCT_BODY()

	FEffect() {}

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Effect" )
	TArray<TSubclassOf<UEffectTrigger>> Triggers;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Effect" )
	TSubclassOf<UEffectAction> EffectAction;
};

struct FEffectInstance
{
	GENERATED_USTRUCT_BODY()

	FEffectInstance( FEffect Effect )
	{
		for ( auto& Trigger : Effect.Triggers )
		{
			if(Trigger != nullptr)
			{
				UEffectTrigger* NewTrigger = NewObject<UEffectTrigger>( (UObject*)GetTransientPackage(), Trigger );
				Triggers.Add( NewTrigger );
			}
		}

		if( Effect.EffectAction != nullptr )
		{
			EffectAction = NewObject<UEffectAction>( (UObject*)GetTransientPackage(), Effect.EffectAction );
		}
	}

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Effect" )
	TArray<UEffectTrigger*> Triggers;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Effect" )
	UEffectAction* EffectAction;
};