// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "PlayerController_Chess.h"
#include "ChessMove.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "GPawn.h"
#include "ChessPiece.h"
#include "EngineUtils.h"


AMainGameMode::AMainGameMode()
{
	PlayerControllerClass = APlayerController_Chess::StaticClass();
	DefaultPawnClass = AHumanPlayer::StaticClass();
	FieldSize = 8;

}

int32 AMainGameMode::GetNextPlayer(int32 Player)
{
	Player++;
	if (!Players.IsValidIndex(Player))
	{
		Player = 0;
	}
	return Player;
}

void AMainGameMode::TurnNextPlayer()
{
	CurrentPlayer = GetNextPlayer(CurrentPlayer);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			// function to delay
			Players[CurrentPlayer]->OnTurn();
		}, 2, false);
	Players[CurrentPlayer]->OnTurn();
}

void AMainGameMode::MovePieceToLocation(AChessPiece* CPiece, FVector2D Location) const
{
	CPiece->SetActorLocation(Field->GetRelativeLocationByXYPosition(Location.X, Location.Y));

}

void AMainGameMode::StartGame()
{
	// Human player starts
	CurrentPlayer = 0;
	for (int32 i = 0; i < Players.Num(); i++)
	{
		Players[i]->PlayerNumber = i;
	}
	// Move counter +=1
	Players[0]->PlayerTeam = true;
	Players[1]->PlayerTeam = false;

	Players[CurrentPlayer]->OnTurn();
}


void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	

	StartGame();

	IsGameOver = false;
	
	if(GFieldClass != nullptr)
	{
		// Spawn Actor di tipo Class e salvo come attributo il puntatore, cos� posso accederci in qualsiasi momento
		Field = GetWorld()->SpawnActor<AGameField>(GFieldClass);

	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("GFieldClass null"));
	}

	
	AHumanPlayer* HumanPlayer = Cast<AHumanPlayer>(*TActorIterator<AHumanPlayer>(GetWorld()));
	// Add Human and AI Player
	Players.Add(HumanPlayer);
	auto AiPlayer = GetWorld()->SpawnActor<ARandomPlayer>();
	Players.Add(AiPlayer);

	// Camera
	FVector CameraPosition = Field->GetActorLocation() + FVector(500, 500, 1000);
	HumanPlayer->SetActorLocationAndRotation(CameraPosition, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());

	// Cast<AHumanPlayer>(Players[CurrentPlayer])->IsMyTurn = true;	
	
}

AChessPiece* AMainGameMode::MakeMove(ChessMove& Move, bool bIsRealMove)
{
	ATile* OldTile = *(this->Field->TileMap.Find(Move.Start));
	ATile* NewTile = *(this->Field->TileMap.Find(Move.End));

	AChessPiece* MovedPiece = OldTile->GetChessPiece();
	AChessPiece* CapturedPiece = NewTile->GetChessPiece();

	// Imposta il pezzo della nuova tile al pezzo spostato,
	// La tile del pezzo spostato a quella nuova,
	// Il pezzo della tile vecchia a nullptr
	// 
	// Cattura:
	// Cancella il pezzo catturato dal TileArray
	// 
	// Mossa reale:
	// Sposta l'attore, cancella pezzo catturato

	if (Move.CapturedChessPiece)
	{
		if (bIsRealMove)
		{
			Move.MovedChessPiece->bHumanTeam ?
				this->Field->WhitePieces.Remove(CapturedPiece) :
				this->Field->BlackPieces.Remove(CapturedPiece);
			
			CapturedPiece->Destroy();
		}
		else
		{
			CapturedPiece->bIsCaptured = true;
		}
	}

	NewTile->SetChessPiece(MovedPiece);

	if (MovedPiece)
	{
		MovedPiece->SetGridPosition(NewTile->GetGridPosition());
		OldTile->SetChessPiece(nullptr);
		// New line
		NewTile->SetTileStatus(MovedPiece->bHumanTeam ? 0 : -1, ETileStatus::OCCUPIED);
		if (bIsRealMove)
		{
			MovePieceToLocation(MovedPiece, NewTile->GetGridPosition());
			OldTile->SetTileStatus(-1, ETileStatus::EMPTY);
		}
	}

	return CapturedPiece;
}



