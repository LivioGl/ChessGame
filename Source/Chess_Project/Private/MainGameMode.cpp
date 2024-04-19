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
	return int32();
}

void AMainGameMode::TurnNextPlayer()
{

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
	IsGameOver = false;
	// Camera
	AHumanPlayer* HumanPlayer = Cast<AHumanPlayer>(*TActorIterator<AHumanPlayer>(GetWorld()));

	if(GFieldClass != nullptr)
	{
		// Spawn Actor di tipo Class e salvo come attributo il puntatore, così posso accederci in qualsiasi momento
		Field = GetWorld()->SpawnActor<AGameField>(GFieldClass);

	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("GFieldClass null"));
	}
	FVector CameraPosition = Field->GetActorLocation() + FVector(500, 500, 1000);
	HumanPlayer->SetActorLocationAndRotation(CameraPosition, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());
	
	// Add Human and AI Player
	Players.Add(HumanPlayer);
	auto AiPlayer = GetWorld()->SpawnActor<ARandomPlayer>();
	Players.Add(AiPlayer);
	this->StartGame();

}



