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
	// create a camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//set the camera as RootComponent
	SetRootComponent(Camera);
	// get the game instance reference
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

//// OnTurn() 
void AHumanPlayer::OnTurn()
{
	IsMyTurn = true;
	// Debug String
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));
	//UMainGameInstance->SetTurnMessage(TEXT("Human Turn"));
}
//
void AHumanPlayer::OnWin()
{
	// Debug String
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Win!"));
	//GameInstance->SetTurnMessage(TEXT("Human Wins!"));
	//GameInstance->IncrementScoreHumanPlayer();
}
//
void AHumanPlayer::OnLose()
{
	// Debug String
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Lose!"));
	//GameInstance->SetTurnMessage(TEXT("Human Loses!"));
}

void AHumanPlayer::OnClick()
{
	// Gamemode reference
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	//Structure containing information about one hit of a trace, such as point of impact and surface normal at that point
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
					auto tileMap = GameMode->Field->TileMap;
					UE_LOG(LogTemp, Warning, TEXT("Move.End contains: %f %f"), Move.End.X, Move.End.Y);
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
				GameMode->ValidMoves.Empty();
				ClickedPiece->GetValidMoves();
				GameMode->Field->HintClearEvent.Broadcast();
				FVector2D EndPiece = FVector2D(ClickedPiece->PieceGridPosition.X, ClickedPiece->PieceGridPosition.Y);
				ChessMove CandidateMove = ChessMove(ClickedPiece, PickedPiece->GetGridPosition(), EndPiece, ClickedPiece);
				if (!GameMode->ValidMoves.Contains(CandidateMove)) return;	
				// Chiamata a MakeMove
				AChessPiece* CapturedPiece = GameMode->MakeMove(CandidateMove, true);
				// FATTO IN MAKEMOVE: ClickedPiece->bIsCaptured = true;
				// Gamefield pointer
				AGameField* Field = GameMode->Field;
				// TODO: chiamata a MakeMove
				// Setting old tile to empty and tile's player owner to -1
				// FATTO IN MAKEMOVE ATile* OldTile = Field->TileMap[PickedPiece->GetGridPosition()];
				// FATTO IN MAKEMOVE OldTile->SetTileStatus(-1, ETileStatus::EMPTY);
				GameMode->ValidMoves.Empty();
				IsMyTurn = false;		
				GameMode->TurnNextPlayer();
				
			}		
		}	

		if (ATile* PickedTile = Cast<ATile>(Hit.GetActor()))
		{
			if (!ClickedPiece)
			{
				return;
			}
			GameMode->Field->HintClearEvent.Broadcast();
			AGameField* Field = GameMode->Field;
			// Moving the piece 
			ATile* NewTile = Field->TileMap[PickedTile->GetGridPosition()];
			FVector NewPosition = Field->GetRelativeLocationByXYPosition(NewTile->GetGridPosition().X, NewTile->GetGridPosition().Y);
			ClickedPiece->SetActorLocation(Field->GetActorLocation() + NewPosition);
			NewTile->SetTileStatus(0, ETileStatus::OCCUPIED);
			// Setting old tile to empty and tile's player owner to -1
			ATile* OldTile = Field->TileMap[ClickedPiece->GetGridPosition()];
			OldTile->SetTileStatus(-1, ETileStatus::EMPTY);
			GameMode->ValidMoves.Empty();
			IsMyTurn = false;

			GameMode->TurnNextPlayer();
		}
	}
}



