#pragma once

#include "ChessPiece.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bishop.generated.h"

class AGameField;

UCLASS()
class CHESS_PROJECT_API ABishop : public AChessPiece
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABishop();
	TArray<ATile*> BishopValidMoves();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};