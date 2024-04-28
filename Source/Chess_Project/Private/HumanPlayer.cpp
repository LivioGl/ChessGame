// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayer.h"
#include "GameField.h"
#include "Tile.h"

// Sets default values
AHumanPlayer::AHumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set this pawn to be controlled by the lowest-numbered player (Human)
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// set the camera as RootComponent
	SetRootComponent(Camera);
	GameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// default init values
	PlayerNumber = -1;
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

// Checking King Security
void AHumanPlayer::OnTurn()
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->IsGameOver) return;
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));

	GameMode->ValidMoves.Empty();
	
	for (auto& Piece : GameMode->Field->WhitePieces)
	{
		Piece->GetValidMoves();
	}
	TArray<ChessMove> MovesToRemove;

	for (auto& Move : GameMode->ValidMoves)
	{
		// Simulate the move by putting second argument to false
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

	// checking for CheckMate
	if (GameMode->ValidMoves.IsEmpty())
	{
		if (King->IsKingUnderCheck(GameMode->Field))
		{
			OnLose();
		}
		else
		{
			OnTie();
		}
	}

}

void AHumanPlayer::OnWin()
{
	// Debug String
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You Win!"));
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->IsGameOver = true;
}

void AHumanPlayer::OnTie()
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("That's a tie!"));
	GameMode->IsGameOver = true;

}

void AHumanPlayer::OnLose()
{
	// Debug String
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You Lose!"));
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->IsGameOver = true;
}

void AHumanPlayer::OnClick()
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	// Structure containing information about one hit of a trace, such as point of impact and surface normal at that point
	// Info about where I clicked
	FHitResult Hit = FHitResult(ForceInit);

	static AChessPiece* ClickedPiece = nullptr;
	// GetHitResultUnderCursor function sends a ray from the mouse position and gives the corresponding hit results
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	// Check if I clicked something and MyTurn is true
	if (Hit.bBlockingHit && IsMyTurn)
	{
		if (AChessPiece* PickedPiece = Cast<AChessPiece>(Hit.GetActor()))
		{
			// Click on a human team piece
			if (PickedPiece->bHumanTeam)
			{
				ClickedPiece = PickedPiece;
				// Remove previous move hints
				GameMode->Field->HintClearEvent.Broadcast();
				// Calculate Valid Moves
				GameMode->ValidMoves.Empty();
				PickedPiece->GetValidMoves();
				FVector2D StartingPosition = FVector2D(PickedPiece->PieceGridPosition.X, PickedPiece->PieceGridPosition.Y);
				for (auto& Move : GameMode->ValidMoves)
				{
					if (GameMode->Field->TileMap.Contains(Move.End))
					{
						ATile* TileToChange = GameMode->Field->TileMap[Move.End];
						UMaterialInterface* MoveHintMaterial = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, *PickedPiece->MoveHint));
						UStaticMeshComponent* MoveHintComp = TileToChange->GetStatMeshComp();
						MoveHintComp->SetMaterial(0, MoveHintMaterial);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("No element"));
						return;
					}
				}
			}
			else
			{
				if (ClickedPiece == nullptr)
				{
					return;
				}
				
				ChessMove CandidateMove = ChessMove(ClickedPiece, ClickedPiece->GetGridPosition(), PickedPiece->GetGridPosition(), PickedPiece);
				if (!GameMode->ValidMoves.Contains(CandidateMove)) return;	
				
				// MakeMove call
				AChessPiece* CapturedPiece = GameMode->MakeMove(CandidateMove, true);
				GameMode->Field->HintClearEvent.Broadcast();
				GameMode->ValidMoves.Empty();
				IsMyTurn = false;		
				GameMode->TurnNextPlayer();
				
			}		
		}	

		// Moving a piece to an empty tile
		if (ATile* PickedTile = Cast<ATile>(Hit.GetActor()))
		{
			if (!ClickedPiece)
			{
				return;
			}

			// Moving the piece 
			ATile* NewTile = GameMode->Field->TileMap[PickedTile->GetGridPosition()];
		
			ChessMove CandidateMove = ChessMove(ClickedPiece, ClickedPiece->GetGridPosition(), NewTile->GetGridPosition());
			if (!GameMode->ValidMoves.Contains(CandidateMove)) return;
			AChessPiece* MovedPiece = GameMode->MakeMove(CandidateMove, true);
			
			GameMode->Field->HintClearEvent.Broadcast();
			GameMode->ValidMoves.Empty();
			IsMyTurn = false;
			GameMode->TurnNextPlayer();
		}
	}
}



