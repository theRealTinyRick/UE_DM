#include <Gameplay/Pawns/DuelPawn.h>

#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include <DMGameInstance.h>
#include <Gameplay/GameState/DMGameState.h>
#include <Gameplay/Actors/ActionManager.h>
#include <Gameplay/Actors/CardActor.h>
#include <Gameplay/GameState/DMGameState.h>


ADuelPawn::ADuelPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates( true );

	MyRoot = CreateDefaultSubobject<USceneComponent>( TEXT( "Pawn Root" ) );
	DeckLocator = CreateDefaultSubobject<USceneComponent>( TEXT( "Deck Locator" ) );
	HandLocator = CreateDefaultSubobject<USceneComponent>( TEXT( "Hand Locator" ) );
	GraveyardLocator = CreateDefaultSubobject<USceneComponent>( TEXT( "Graveyard Locator" ) );
	BattleZoneLocator = CreateDefaultSubobject<USceneComponent>( TEXT( "Battle Zone Locator" ) );
	ShieldZoneLocator = CreateDefaultSubobject<USceneComponent>( TEXT( "Shield Zone Locator" ) );
	ManaZoneLocator = CreateDefaultSubobject<USceneComponent>( TEXT( "Mana Zone Locator" ) );

	SetRootComponent( MyRoot );
	DeckLocator->SetupAttachment( RootComponent );
	HandLocator->SetupAttachment( RootComponent );
	GraveyardLocator->SetupAttachment( RootComponent );
	BattleZoneLocator->SetupAttachment( RootComponent );
	ShieldZoneLocator->SetupAttachment( RootComponent );
	ManaZoneLocator->SetupAttachment( RootComponent );
}

void ADuelPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ADuelPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//ECC_GameTraceChannel1 -- card
	//ECC_GameTraceChannel2 -- board

	if ( APlayerController* PC = Cast<APlayerController>( GetController() ) )
	{
		FHitResult TraceHitResult_One;
		FHitResult TraceHitResult_Two;
		FVector TargetPoint;
		
		PC->GetHitResultUnderCursor( ECC_GameTraceChannel1, true, TraceHitResult_One );
		PC->GetHitResultUnderCursor( ECC_GameTraceChannel2, true, TraceHitResult_Two );
		DrawDebugSphere( GetWorld(), TraceHitResult_Two.ImpactPoint, 20, 20, FColor::Cyan, false, -1, 0, 1 );

		if(TraceHitResult_One.Actor != nullptr)
		{
			ACardActor* CardActor = Cast<ACardActor>( TraceHitResult_One.Actor );
			if(CardActor != nullptr)
			{
				if(CardActor != CurrentHoveredCard)
				{
					if(CardActor->GetCardMesh()->GetCollisionObjectType() == ECC_GameTraceChannel2)
					{
						DM_SCREENERROR( "Its channel 2", -1 );
					}
					if( CardActor->GetCardMesh()->GetCollisionObjectType() == ECC_GameTraceChannel1 )
					{
						DM_SCREENERROR( "Its channel 1", -1 );
					}
					CardHoveredEvent.Broadcast(CardActor);
				}
			}
			else
			{
				CurrentHoveredCard = nullptr;
			}
		}
	}
}

void ADuelPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	PlayerInputComponent->BindAction( "LeftMouse", EInputEvent::IE_Pressed, this, &ADuelPawn::OnClick );
	PlayerInputComponent->BindAction( "LeftMouse", EInputEvent::IE_Pressed, this, &ADuelPawn::OnRelease );
}

void ADuelPawn::SetPlayerNumber( int NewPlayerNumber )
{
	FindActionManager();

	Duelist = NEW_OBJECT( UDuelist, UDuelist::StaticClass() );
	PlayerNumber = NewPlayerNumber;
	Duelist->PlayerNumber = PlayerNumber;
	Deck = Cast<UDMGameInstance>(GetWorld()->GetGameInstance())->PlayerChosenDeck;
	Duelist->SetDeck( Deck->GetDeck() );

	bIsPlayerNumberSet = true;
}

void ADuelPawn::FindActionManager()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass( GetWorld(), AActionManager::StaticClass(), FoundActors );
	if(FoundActors.Num() > 0)
	{
		ActionManager = Cast<AActionManager>( FoundActors[0] );
		ActionManager->ShieldAddedEvent.AddDynamic( this, &ADuelPawn::OnCardShouldSpawn );
		ActionManager->CardDrawnEvent.AddDynamic( this, &ADuelPawn::OnCardShouldSpawn );
	}
}

void ADuelPawn::OnClick()
{
	if(CurrentHoveredCard != nullptr)
	{
		CurrentClickedCard = CurrentHoveredCard;
		CardClickedEvent.Broadcast( CurrentClickedCard );
	}
}

void ADuelPawn::OnRelease()
{
	if ( CurrentClickedCard != nullptr )
	{
		CardReleasedEvent.Broadcast( CurrentClickedCard );
		CurrentClickedCard = nullptr;
	}
}

void ADuelPawn::OnCardShouldSpawn( UCard* TargetCard, UDuelist* TargetDuelist )
{
	if(CardClass == nullptr)
	{
		CardClass = ACardActor::StaticClass();
	}

	if(GetDuelist() == TargetDuelist)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACardActor* NewCardActor = GetWorld()->SpawnActor<ACardActor>( CardClass, DeckLocator != nullptr ? DeckLocator->GetComponentLocation() :  FVector(), DeckLocator != nullptr ? DeckLocator->GetComponentRotation() : FRotator(), SpawnParams );
		if(NewCardActor != nullptr)
		{
			NewCardActor->SetCard( TargetCard, this );
		}
	}
}

//void ADuelPawn::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const 
//{
//	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
//	//DOREPLIFETIME( ADuelPawn, PlayerNumber );
//}