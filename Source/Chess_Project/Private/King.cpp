// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "MainGameMode.h"

// Sets default values
AKing::AKing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Scene component
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);
	// // File Path to assign correct material
	MaterialBlack = TEXT("/Game/Materials/MI_BlackKing");
	MaterialWhite = TEXT("/Game/Materials/MI_WhiteKing");
	Type = PieceType::KING;
}

void AKing::GetValidMoves()
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	// Current King position saved in this pointer
	FVector2D KingCurrentPosition(PieceGridPosition.X, PieceGridPosition.Y);
	ATile* CurrentPosition = Field->TileMap[(KingCurrentPosition)];
	// Directions of possibile moves
	FVector2D KMovements[8];
	KMovements[0] = FVector2D(0, 1);
	KMovements[1] = FVector2D(1, 1);
	KMovements[2] = FVector2D(1, 0);
	KMovements[3] = FVector2D(1, -1);
	KMovements[4] = FVector2D(0, -1);
	KMovements[5] = FVector2D(-1, -1);
	KMovements[6] = FVector2D(-1, 0);
	KMovements[7] = FVector2D(-1, 1);
	for (int i = 0; i < 8; i++)
	{
		while (auto NewTiles = Field->TileMap.Find(KingCurrentPosition + KMovements[i]))
		{
			// Check the directions where Bishop is able to move and gets empty tiles or enemy pieces
			if ((*NewTiles)->GetTileStatus() == ETileStatus::EMPTY || (*NewTiles)->GetChessPiece()->bHumanTeam != this->bHumanTeam)
			{
				// Save the move in a gamemode array
				ChessMove KingSingleMove(this, KingCurrentPosition, KingCurrentPosition + KMovements[i], (*NewTiles)->GetChessPiece());
				GameMode->ValidMoves.Add(KingSingleMove);
			}
			if ((*NewTiles)->GetTileStatus() == ETileStatus::OCCUPIED) break;
			
			i++;
		}
	}
}

// Called when the game starts or when spawned
void AKing::BeginPlay()
{
	Super::BeginPlay();
}

bool AKing::IsKingUnderCheck(AGameField* Field)
{
	// Under Check from Queen or Rook
	{
		FVector2D Horizontal[4];
		Horizontal[0] = FVector2D(1, 0);
		Horizontal[1] = FVector2D(-1, 0);
		Horizontal[2] = FVector2D(0, -1);
		Horizontal[3] = FVector2D(0, 1);
		
		for(int a = 0; a < 4; a++)
		{
			while (auto NewTile = Field->TileMap.Find(this->GetGridPosition() + Horizontal[a]))
			{
				auto Piece = (*NewTile)->GetChessPiece();
				if (Piece != nullptr)
				{
					if ((Piece->Type == PieceType::ROOK || Piece->Type == PieceType::QUEEN)
						&& Piece->bHumanTeam != this->bHumanTeam)
						return true;
					else break;
				}

				Horizontal[a].X == 0 ? 0 : Horizontal[a].X > 0 ? Horizontal[a].X += 1 : Horizontal[a].X -= 1;
				Horizontal[a].Y == 0 ? 0 : Horizontal[a].Y > 0 ? Horizontal[a].Y += 1 : Horizontal[a].Y -= 1;

			}
		}
	}

	// Under Check from enemy's King
	{
		FVector2D KingMoves[8];
		KingMoves[0] = FVector2D(1, 1);
		KingMoves[1] = FVector2D(1, 0);
		KingMoves[2] = FVector2D(1, -1);
		KingMoves[3] = FVector2D(0, -1);
		KingMoves[4] = FVector2D(-1, -1);
		KingMoves[5] = FVector2D(-1, 0);
		KingMoves[6] = FVector2D(-1, 1);
		KingMoves[7] = FVector2D(0, 1);
		for (int b = 0; b < 8; b++)
		{
			if (auto NewTile = Field->TileMap.Find(this->GetGridPosition() + KingMoves[b]))
			{
				auto Piece = (*NewTile)->GetChessPiece();
				if (Piece == nullptr) continue;
				if (Piece->Type == PieceType::KING  && Piece->bHumanTeam != this->bHumanTeam) return true;
			}
			
		}

	}
	
	// Under Check from Knight
	{
		FVector2D KnightMoves[8];
		KnightMoves[0] = FVector2D(1, 2);
		KnightMoves[1] = FVector2D(2, 1);
		KnightMoves[2] = FVector2D(2, -1);
		KnightMoves[3] = FVector2D(-1, 2);
		KnightMoves[4] = FVector2D(-2, 1);
		KnightMoves[5] = FVector2D(1, -2);
		KnightMoves[6] = FVector2D(-2, -1);
		KnightMoves[7] = FVector2D(-1, -2);
		for (int c = 0; c < 8; c++)
		{
			if (auto NewTile = Field->TileMap.Find(this->GetGridPosition() + KnightMoves[c]))
			{
				auto Piece = (*NewTile)->GetChessPiece();
				if (Piece == nullptr) continue;
				if (Piece->Type == PieceType::KNIGHT && Piece->bHumanTeam != this->bHumanTeam) return true;
			}
		}
	}
	
	// Under Check from Bishop or Queen
	{
		FVector2D Diagonals[4];
		Diagonals[0] = FVector2D(1, 1);
		Diagonals[1] = FVector2D(-1, 1);
		Diagonals[2] = FVector2D(-1, -1);
		Diagonals[3] = FVector2D(1, -1);
		for (int d = 0; d < 4; d++)
		{
			while (auto NewTile = Field->TileMap.Find(this->GetGridPosition() + Diagonals[d]))
			{
				auto Piece = (*NewTile)->GetChessPiece();
				if (Piece != nullptr) 
				{
					if ((Piece->Type == PieceType::BISHOP || Piece->Type == PieceType::QUEEN) && Piece->bHumanTeam != this->bHumanTeam)
					{
						return true;
					}
					else break;
				}

				Diagonals[d].X > 0 ? Diagonals[d].X += 1 : Diagonals[d].X -= 1;
				Diagonals[d].Y > 0 ? Diagonals[d].Y += 1 : Diagonals[d].Y -= 1;

			}
		}
	}

	// Under Check from Pawn
	{
		bool bIsWhite = this->bHumanTeam;

		if (auto NewPiece = Field->TileMap.Find(this->GetGridPosition() + FVector2D(bIsWhite ? 1 : -1, 1)))
		{
			AChessPiece* CPiece = (*NewPiece)->GetChessPiece();
			if (CPiece && CPiece->Type == PieceType::PAWN && CPiece->bHumanTeam != this->bHumanTeam)
				return true;
		}

		if (auto TileToCheck = Field->TileMap.Find(this->GetGridPosition() + FVector2D(bIsWhite ? 1 : -1, -1)))
		{
			AChessPiece* CPiece = (*TileToCheck)->GetChessPiece();
			if (CPiece && CPiece->Type == PieceType::PAWN && CPiece->bHumanTeam != this->bHumanTeam)
				return true;
		}
	}
	// All controls finished, king is not under check
	return false;
}

// Called every frame
void AKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}