
#include <Gameplay/Actors/CardActor.h>
#include "Components/StaticMeshComponent.h"
#include <Gameplay/Pawns/DuelPawn.h>
#include "DrawDebugHelpers.h"

ACardActor::ACardActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent( CreateDefaultSubobject<USceneComponent>( TEXT( "Root" ) ) );
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Card Mesh" ) );
	CardBackMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Card Back Mesh" ) );

	CardMesh->SetupAttachment( RootComponent );
	CardBackMesh->SetupAttachment( RootComponent );

	Tags = { CARD_TAG };
}

void ACardActor::SetCard( UCard* CardToSet, ADuelPawn* NewDuelPawnOwner )
{
	DuelPawnOwner = NewDuelPawnOwner;

	Card = CardToSet;
	if ( Card != nullptr )
	{
		CardMesh->SetMaterial( 0, Card->GetCardMaterial() );
	}
}

void ACardActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACardActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if ( Card == nullptr || DuelPawnOwner == nullptr )
	{
		return;
	}

	FVector TargetLocation;
	FRotator TargetRotation;
	FVector Right = DuelPawnOwner->GetActorRightVector();
	ECardLocation CurrentLocation = Card->GetCurrentLocation();
	TArray<UCard*> Cards = Card->GetCardOwner()->GetCollection( CurrentLocation )->GetCards();
	int Index = Cards.IndexOfByKey( Card );
	bool bIsCurrentClickedCard = DuelPawnOwner->GetCurrentClickedCard() == this;

	if(bIsCurrentClickedCard)
	{
		//get current mouse board location
	}
	else
	{
		// update my location
		switch ( CurrentLocation )
		{
		case ECardLocation::DECK:
			TargetRotation = DuelPawnOwner->GetDeckLocator()->GetComponentRotation();
			TargetLocation = DuelPawnOwner->GetDeckLocator()->GetComponentLocation();
			break;

		case ECardLocation::HAND:
			TargetRotation = DuelPawnOwner->GetHandLocator()->GetComponentRotation();
			TargetLocation = DuelPawnOwner->GetHandLocator()->GetComponentLocation();
			if ( Cards.Contains( Card ) )
			{
				TargetLocation = TargetLocation + (-Right * (Index * (ApproximateCardHeight * 0.9f)));
			}
			break;

		case ECardLocation::BATTLEZONE:
			break;

		case ECardLocation::SHIELDZONE:
			TargetLocation = DuelPawnOwner->GetShieldZoneLocator()->GetComponentLocation();
			TargetRotation = DuelPawnOwner->GetShieldZoneLocator()->GetComponentRotation();
			if ( Cards.Contains( Card ) )
			{
				TargetLocation = TargetLocation + (-Right * (Index * ApproximateCardHeight));
			}
			break;

		case ECardLocation::MANAZONE:
			break;
		case ECardLocation::GRAVEYARD:
			break;
		case ECardLocation::REMOVEDFROMGAME:
			break;
		case ECardLocation::NONE:
			return;
		}
	}

	SetActorLocation( TargetLocation );
	SetActorRotation( TargetRotation );
}

