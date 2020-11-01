
#include <Gameplay/Actors/CardActor.h>
#include "Components/StaticMeshComponent.h"

ACardActor::ACardActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent( CreateDefaultSubobject<USceneComponent>( TEXT( "Root" ) ) );
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Card Mesh" ) );
	CardBackMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Card Back Mesh" ) );

	CardMesh->SetupAttachment( RootComponent );
	CardBackMesh->SetupAttachment( RootComponent );
}

void ACardActor::SetCard( UCard* CardToSet )
{
	Card = CardToSet;
	if(Card != nullptr)
	{
		// update card mesh
		CardMesh->OverrideMaterials = { Card->GetCardMaterial() };
	}
}

void ACardActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

