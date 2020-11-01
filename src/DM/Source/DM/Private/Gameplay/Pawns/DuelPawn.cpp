#include <Gameplay/Pawns/DuelPawn.h>

#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameState.h"
#include "Kismet/GameplayStatics.h"

#include <DMGameInstance.h>
#include <Framework/Duelist/Duelist.h>
#include <Framework/Deck.h>
#include <Gameplay/GameState/DMGameState.h>
#include <Gameplay/Actors/ActionManager.h>
#include <Gameplay/Actors/CardActor.h>


ADuelPawn::ADuelPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates( true );

	MyRoot = CreateDefaultSubobject<USceneComponent>( TEXT( "Pawn Root" ) );
	CardSpawnPoint = CreateDefaultSubobject<USceneComponent>( TEXT( "Card Spawn Point" ) );

	SetRootComponent( MyRoot );
	CardSpawnPoint->SetupAttachment( RootComponent );
}

void ADuelPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ADuelPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ADuelPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
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

		ACardActor* NewCardActor = GetWorld()->SpawnActor<ACardActor>( CardClass, CardSpawnPoint != nullptr ? CardSpawnPoint->GetComponentLocation() :  FVector(), CardSpawnPoint != nullptr ? CardSpawnPoint->GetComponentRotation() : FRotator(), SpawnParams );
		if(NewCardActor != nullptr)
		{
			NewCardActor->SetCard( TargetCard );
		}
	}
}

//void ADuelPawn::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const 
//{
//	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
//	//DOREPLIFETIME( ADuelPawn, PlayerNumber );
//}