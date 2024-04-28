// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"
#include "MainGameMode.h"

// Sets default values
AGameField::AGameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Dimensions of the field
	Size = 8;
	TileSize = 120;
	PieceSize = 110;
}

void AGameField::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
	SpawnPieces(WhitePieces, BlackPieces);
	
}

// Assigning material function
void AGameField::ChangeMaterial(AChessPiece* S, bool IsBlack)
{
	UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, IsBlack ? *S->MaterialBlack : *S->MaterialWhite));
	UStaticMeshComponent* Comp = S->GetStatMeshComp();
	Comp->SetMaterial(0, Material);
}

void AGameField::GenerateField()
{
	// Spawning chess board
	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
			ATile* Obj;
			if ((x + y) % 2 == 0)
			{
				Obj = GetWorld()->SpawnActor<ATile>(TileClassBlack, Location, FRotator::ZeroRotator);
				HintClearEvent.AddDynamic(Obj, &ATile::ResetMaterial);
			}
			else
			{
				Obj = GetWorld()->SpawnActor<ATile>(TileClassWhite, Location, FRotator::ZeroRotator);
				HintClearEvent.AddDynamic(Obj, &ATile::ResetMaterial);
			}
			const float TileScale = TileSize / 100;
			
			Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
			Obj->SetGridPosition(x, y);
			TileArray.Add(Obj);
			TileMap.Add(FVector2D(x, y), Obj);
		}
	}
}

void AGameField::SpawnPieces(TArray<AChessPiece*> &WPieces, TArray<AChessPiece*> &BPieces)
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	// Spawning White Pawns
	for (int32 b = 0; b < 8; b++)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(1, b);
		AGPawn* WhitePawn;
		WhitePawn = GetWorld()->SpawnActor<AGPawn>(GPawn, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		WhitePawn->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		WhitePawn->SetGridPosition(1, b);
		ChangeMaterial(WhitePawn, false);
		this->TileMap[FVector2D(1, b)]->SetTileStatus(0, ETileStatus::OCCUPIED);
		this->TileMap[FVector2D(1, b)]->SetChessPiece(WhitePawn);
		WhitePieces.Add(WhitePawn);
	}
	// Spawning Black Pawns
	for (int32 b = 0; b < 8; b++)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(6, b);
		AGPawn* BlackPawn;
		BlackPawn = GetWorld()->SpawnActor<AGPawn>(GPawn, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		BlackPawn->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		BlackPawn->SetGridPosition(6, b);
		// Setting team to AI team
		BlackPawn->bHumanTeam = false;
		ChangeMaterial(BlackPawn, true);
		this->TileMap[FVector2D(6, b)]->SetTileStatus(1, ETileStatus::OCCUPIED);
		this->TileMap[FVector2D(6, b)]->SetChessPiece(BlackPawn);
		BlackPieces.Add(BlackPawn);
	}
	// Spawning White Bishops
	for (int32 b = 2; b < 6; b+=3)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(0, b);
		ABishop* WhiteBishop;
		WhiteBishop = GetWorld()->SpawnActor<ABishop>(Bishop, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		WhiteBishop->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		WhiteBishop->SetGridPosition(0, b);
		ChangeMaterial(WhiteBishop, false);
		this->TileMap[FVector2D(0, b)]->SetTileStatus(0, ETileStatus::OCCUPIED);
		this->TileMap[FVector2D(0, b)]->SetChessPiece(WhiteBishop);
		WhitePieces.Add(WhiteBishop);
	}
	// Spawning Black Bishops
	for (int32 b = 2; b < 6; b += 3)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(7, b);
		ABishop* BlackBishop;
		BlackBishop = GetWorld()->SpawnActor<ABishop>(Bishop, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		BlackBishop->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		BlackBishop->SetGridPosition(7, b);
		// Setting team to AI team
		BlackBishop->bHumanTeam = false;
		ChangeMaterial(BlackBishop, true);
		this->TileMap[FVector2D(7, b)]->SetTileStatus(1, ETileStatus::OCCUPIED);
		this->TileMap[FVector2D(7, b)]->SetChessPiece(BlackBishop);
		BlackPieces.Add(BlackBishop);
	}
	// Spawning White Rooks
	for (int32 b = 0; b < 9; b += 7)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(0, b);
		ARook* WhiteRook;
		WhiteRook = GetWorld()->SpawnActor<ARook>(Rook, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		WhiteRook->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		WhiteRook->SetGridPosition(0, b);
		ChangeMaterial(WhiteRook, false);
		this->TileMap[FVector2D(0, b)]->SetTileStatus(0, ETileStatus::OCCUPIED);
		this->TileMap[FVector2D(0, b)]->SetChessPiece(WhiteRook);
		WhitePieces.Add(WhiteRook);
	}

	// Spawning Black Rooks
	for (int32 b = 0; b < 9; b += 7)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(7, b);
		ARook* BlackRook;
		BlackRook = GetWorld()->SpawnActor<ARook>(Rook, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		BlackRook->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		BlackRook->SetGridPosition(7, b);
		// Setting team to AI team
		BlackRook->bHumanTeam = false;
		ChangeMaterial(BlackRook, true);
		this->TileMap[FVector2D(7, b)]->SetTileStatus(1, ETileStatus::OCCUPIED);
		this->TileMap[FVector2D(7, b)]->SetChessPiece(BlackRook);
		BlackPieces.Add(BlackRook);
	}
	// Spawning White King
	FVector WhiteKingLocation = AGameField::GetRelativeLocationByXYPosition(0, 4);
	AKing* WhiteKing;
	WhiteKing = GetWorld()->SpawnActor<AKing>(King, WhiteKingLocation, FRotator::ZeroRotator);
	const float PieceScale = PieceSize / 100;
	WhiteKing->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
	WhiteKing->SetGridPosition(0, 4);
	ChangeMaterial(WhiteKing, false);
	this->TileMap[FVector2D(0, 4)]->SetTileStatus(0, ETileStatus::OCCUPIED);
	this->TileMap[FVector2D(0, 4)]->SetChessPiece(WhiteKing);
	WhitePieces.Add(WhiteKing);
	GameMode->Players[0]->King = WhiteKing;

	// Spawning Black King
	FVector BlackKingLocation = AGameField::GetRelativeLocationByXYPosition(7, 4);
	AKing* BlackKing;
	BlackKing = GetWorld()->SpawnActor<AKing>(King, BlackKingLocation, FRotator::ZeroRotator);
	BlackKing->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
	BlackKing->SetGridPosition(7, 4);
	// Setting team to AI team
	BlackKing->bHumanTeam = false;
	ChangeMaterial(BlackKing, true);
	this->TileMap[FVector2D(7, 4)]->SetTileStatus(1, ETileStatus::OCCUPIED);
	this->TileMap[FVector2D(7, 4)]->SetChessPiece(BlackKing);
	BlackPieces.Add(BlackKing);
	GameMode->Players[1]->King = BlackKing;
	
	// Spawning White Queen
	FVector WhiteQueenLocation = AGameField::GetRelativeLocationByXYPosition(0, 3);
	AQueen* WhiteQueen;
	WhiteQueen = GetWorld()->SpawnActor<AQueen>(Queen, WhiteQueenLocation, FRotator::ZeroRotator);
	WhiteQueen->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
	WhiteQueen->SetGridPosition(0, 3);
	ChangeMaterial(WhiteQueen, false);
	this->TileMap[FVector2D(0, 3)]->SetTileStatus(0, ETileStatus::OCCUPIED);
	this->TileMap[FVector2D(0, 3)]->SetChessPiece(WhiteQueen);
	WhitePieces.Add(WhiteQueen);

	// Spawning Black Queen
	FVector BlackQueenLocation = AGameField::GetRelativeLocationByXYPosition(7, 3);
	AQueen* BlackQueen;
	BlackQueen = GetWorld()->SpawnActor<AQueen>(Queen, BlackQueenLocation, FRotator::ZeroRotator);
	BlackQueen->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
	BlackQueen->SetGridPosition(7, 3);
	// Setting team to AI team
	BlackQueen->bHumanTeam = false;
	ChangeMaterial(BlackQueen, true);
	this->TileMap[FVector2D(7, 3)]->SetTileStatus(1, ETileStatus::OCCUPIED);
	this->TileMap[FVector2D(7, 3)]->SetChessPiece(BlackQueen);
	BlackPieces.Add(BlackQueen);

	// Spawning White Knights
	for (int32 b = 1; b < 7; b += 5)
	{
		FVector WhiteKnightsLocation = AGameField::GetRelativeLocationByXYPosition(0, b);
		AKnight* WhiteKnight = GetWorld()->SpawnActor<AKnight>(Knight, WhiteKnightsLocation, FRotator::ZeroRotator);
		WhiteKnight->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		WhiteKnight->SetGridPosition(0, b);
		ChangeMaterial(WhiteKnight, false);
		this->TileMap[FVector2D(0, b)]->SetTileStatus(0, ETileStatus::OCCUPIED);
		this->TileMap[FVector2D(0, b)]->SetChessPiece(WhiteKnight);
		WhitePieces.Add(WhiteKnight);
	}

	// Spawning Black Knights
	for (int32 b = 1; b < 7; b += 5)
	{
		FVector BlackKnightsLocation = AGameField::GetRelativeLocationByXYPosition(7, b);
		AKnight* BlackKnight;
		BlackKnight = GetWorld()->SpawnActor<AKnight>(Knight, BlackKnightsLocation, FRotator::ZeroRotator);
		BlackKnight->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		BlackKnight->SetGridPosition(7, b);
		// Setting team to AI team
		BlackKnight->bHumanTeam = false;
		ChangeMaterial(BlackKnight, true);
		this->TileMap[FVector2D(7, b)]->SetTileStatus(1, ETileStatus::OCCUPIED);
		this->TileMap[FVector2D(7, b)]->SetChessPiece(BlackKnight);
		BlackPieces.Add(BlackKnight);
	}
}

TArray<ATile*>& AGameField::GetTileArray()
{
	return TileArray;
}

FVector AGameField::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const
{
	return TileSize * FVector(InX, InY, 0);

}

FVector2D AGameField::GetXYPositionByRelativeLocation(const FVector& Location) const
{
	const double x = Location[0] / (TileSize);
	const double y = Location[1] / (TileSize);
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("x=%f,y=%f"), x, y));
	return FVector2D(x, y);
}

inline bool AGameField::IsValidPosition(const FVector2D Position) const
{
	return 0 <= Position[0] && Position[0] < Size && 0 <= Position[1] && Position[1] < Size;
}


