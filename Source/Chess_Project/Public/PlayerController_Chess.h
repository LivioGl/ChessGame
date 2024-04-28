// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HumanPlayer.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerController_Chess.generated.h"

UCLASS()
class CHESS_PROJECT_API APlayerController_Chess : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerController_Chess();

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* ChessContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ClickAction;

	void ClickOnGrid();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
