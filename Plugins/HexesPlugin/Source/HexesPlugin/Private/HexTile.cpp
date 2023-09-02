// Fill out your copyright notice in the Description page of Project Settings.


#include "HexTile.h"
#include "Components/StaticMeshComponent.h"
#include "HexMap.h"

// Sets default values
AHexTile::AHexTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh"));
	TileMesh->SetupAttachment(RootComponent);

	ParentMap = nullptr;

	TileType = EHexTileType::Default;
}

// Called when the game starts or when spawned
void AHexTile::BeginPlay()
{
	Super::BeginPlay();
	
	Material = UMaterialInstanceDynamic::Create(MaterialClass, this);
	TileMesh->SetMaterial(0, Material);

	OnClicked.AddDynamic(this, &AHexTile::OnTileClicked);
}

// Called every frame
void AHexTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexTile::MakeObstacle()
{
	TileType = EHexTileType::Obstacle;

	OnTileUpdated();
	if (ParentMap)
	{
		ParentMap->OnTileUpdated(this);
	}
}

void AHexTile::OnTileClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	if (ParentMap)
	{
		ParentMap->SelectTile(this);
	}
}

