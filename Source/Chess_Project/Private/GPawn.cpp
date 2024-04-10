// Fill out your copyright notice in the Description page of Project Settings.


#include "GPawn.h"

// Sets default values
AGPawn::AGPawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);
}

// Called when the game starts or when spawned
void AGPawn::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* AGPawn::GetStatMeshComp()
{
	return StaticMeshComponent;

}

