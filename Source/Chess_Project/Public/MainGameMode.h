// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameField.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_PROJECT_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Puntatore GameField: lo sfrutto per il riferimento alla GameField
	UPROPERTY(VisibleAnywhere)
	AGameField* Field;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	// Creare attore campo
	// Proprietà di riferimento alla classe della GameField
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGameField> GFieldClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
