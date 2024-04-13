// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayer.h"
#include "Tile.h"

// Sets default values
AHumanPlayer::AHumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set this pawn to be controlled by the lowest-numbered player (Human)
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// create a camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//set the camera as RootComponent
	SetRootComponent(Camera);
	// get the game instance reference
	GameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// default init values
	PlayerNumber = -1;
	//Sign = ESign::E;
}

// Called when the game starts or when spawned
void AHumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHumanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
/*
// OnTurn() 
void AHumanPlayer::OnTurn()
{
	IsMyTurn = true;
	// Debug String
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));
	GameInstance->SetTurnMessage(TEXT("Human Turn"));
}

void AHumanPlayer::OnWin()
{
	// Debug String
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Win!"));
	GameInstance->SetTurnMessage(TEXT("Human Wins!"));
	GameInstance->IncrementScoreHumanPlayer();
}

void AHumanPlayer::OnLose()
{
	// Debug String
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Lose!"));
	GameInstance->SetTurnMessage(TEXT("Human Loses!"));
}
*/
void AHumanPlayer::OnClick()
{
	/*
	//Structure containing information about one hit of a trace, such as point of impact and surface normal at that point
	// Info about where I clicked
	FHitResult Hit = FHitResult(ForceInit);
	// GetHitResultUnderCursor function sends a ray from the mouse position and gives the corresponding hit results
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);

	// if line 76 is an error source, make sure you included the correct file	

	// Check if I clicked something and MyTurn is true
	if (Hit.bBlockingHit && IsMyTurn)
	{
		if (ATile* CurrTile = Cast<ATile>(Hit.GetActor()))
		{
			if (CurrTile->GetTileStatus() == ETileStatus::EMPTY)
			{
				// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("clicked"));
				CurrTile->SetTileStatus(PlayerNumber, ETileStatus::OCCUPIED);
				FVector SpawnPosition = CurrTile->GetActorLocation();
				ATTT_GameMode* GameMode = Cast<ATTT_GameMode>(GetWorld()->GetAuthGameMode());
				GameMode->SetCellSign(PlayerNumber, SpawnPosition);
				IsMyTurn = false;
			}
		}
	}
*/
}

