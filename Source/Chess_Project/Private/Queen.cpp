// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"

// Sets default values
AQueen::AQueen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	MaterialBlack = TEXT("/Game/Materials/MI_BlackQueen");
	MaterialWhite = TEXT("/Game/Materials/MI_WhiteQueen");

}

void AQueen::GetValidMoves()
{

}


// Called when the game starts or when spawned
void AQueen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQueen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}