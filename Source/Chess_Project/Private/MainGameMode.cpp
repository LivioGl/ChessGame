// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "GPawn.h"
#include "ChessPiece.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	if(GFieldClass)
	{
		// Spawn Actor di tipo Class e salvo come attributo il puntatore, così posso accederci in qualsiasi momento
		Field = GetWorld()->SpawnActor<AGameField>(GFieldClass);

	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("GFieldClass null"));
	}

}


// const TArray<FString> Materials = {"WhitePawn", "BlackPawn", "WhiteKing", "BlackKing", "WhiteQueen", "BlackQueen", "WhiteRook", "BlackRook", "WhiteBishop", "BlackBishop", "WhiteKnight", "BlackKnight"};

// Aggiungere puntatore nell'input di questa funzione, deve riconoscere Obj
/*
void AMainGameMode::ChangeMaterial(AGPawn* P, FString F)
{
	UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, *("/Game/Materials/" + F)));
	// Problema funzione GetStatMeshComp()
	UStaticMeshComponent* Comp = P->GetStatMeshComp();
	Comp->SetMaterial(0, Material);
	
}
*/
