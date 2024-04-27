// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPlayer.h"

// Sets default values
ARandomPlayer::ARandomPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called when the game starts or when spawned
void ARandomPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARandomPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARandomPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARandomPlayer::OnTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tocca al Bot!"));
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {

	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->IsGameOver) return;
	
	for (auto& Piece : GameMode->Field->BlackPieces)
	{
		Piece->GetValidMoves();
	}
	TArray<ChessMove> MovesToRemove;

	for (auto& Move : GameMode->ValidMoves)
	{
		// Simulate the move
		AChessPiece* MPiece = GameMode->MakeMove(Move, false);

		if (King->IsKingUnderCheck(GameMode->Field))
		{
			MovesToRemove.Add(Move);
		}
		GameMode->UnmakeMove(Move);
	}
	for (auto& Move : MovesToRemove)
	{
		GameMode->ValidMoves.Remove(Move);
	}


	if (GameMode->ValidMoves.IsEmpty())
	{
		if (King->IsKingUnderCheck(GameMode->Field))
		{
			OnLose();
			GameMode->IsGameOver = true;
		}
		else
		{
			OnTie();
			GameMode->IsGameOver = true;
		}
	}

	if (GameMode->IsGameOver) return;
	// Black Pieces Array
	
	int32 MoveRand = FMath::Rand() % GameMode->ValidMoves.Num();
	AChessPiece* BlackMovedPiece = GameMode->MakeMove(GameMode->ValidMoves[MoveRand], true);
	GameMode->ValidMoves.Empty();
	GameMode->TurnNextPlayer();

	}, 2, false);
}

void ARandomPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Bot wins!"));
}

void ARandomPlayer::OnTie()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("That's a tie!"));
}

void ARandomPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("The bot is a loser!"));
}

