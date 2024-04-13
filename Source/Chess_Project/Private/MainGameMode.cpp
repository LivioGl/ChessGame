// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "PlayerController_Chess.h"
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
	FVector Pippo = Field->GetActorLocation() + FVector(500, 500, 1000);
	//float CameraPosX = ((Field->TileSize * (FieldSize + ((FieldSize - 1) * Field->NormalizedCellPadding) - (FieldSize - 1))) / 2) - (Field->TileSize / 2);
	// FVector CameraPos(CameraPosX, CameraPosX, 1000.0f);
	HumanPlayer->SetActorLocationAndRotation(Pippo, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());
}



