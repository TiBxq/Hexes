// Fill out your copyright notice in the Description page of Project Settings.


#include "HexPawn.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHexPawn::AHexPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHexPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHexPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

