// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

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