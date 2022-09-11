// Fill out your copyright notice in the Description page of Project Settings.


#include "HexMap.h"
#include "Hexes/HexTile.h"

// Sets default values
AHexMap::AHexMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentSelectionType = EHexSelectionType::Line;
}

// Called when the game starts or when spawned
void AHexMap::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<FHex> AHexMap::GenerateMap() const
{
	FHex ZeroHex(0, 0);

	TArray<FHex> Result;
	Result.Add(ZeroHex);

	for (int32 k = 0; k < MapSize; ++k)
	{
		TArray<FHex> HexesToAdd;
		for (const FHex& Hex : Result)
		{
			for (int32 i = 0; i < 6; ++i)
			{
				FHex NewHex = Hex.GetNeighbor(i);
				if (!Result.Contains(NewHex) && !HexesToAdd.Contains(NewHex))
				{
					HexesToAdd.Add(NewHex);
				}
			}
		}

		for (const FHex& Hex : HexesToAdd)
		{
			Result.Add(Hex);
		}
	}
	return Result;
}

void AHexMap::SpawnMap(const TArray<FHex>& Source)
{
	TilesList.Empty();
	HexesList = Source;
	for (const FHex& Hex : Source)
	{
		float x = HexSize * (3.f / 2.f * Hex.q);
		float y = HexSize * (FMath::Sqrt(3.f) / 2.f * Hex.q + FMath::Sqrt(3.f) * Hex.r);
		FVector Position(x, y, 0.f);

		FActorSpawnParameters Params;
		AHexTile* SpawnedTile = GetWorld()->SpawnActor<AHexTile>(HexActorClass, Position, FRotator(0.f), Params);
		if (SpawnedTile)
		{
			SpawnedTile->SetHex(Hex);
			SpawnedTile->SetMap(this);
			SpawnedTile->Init();
		}
		TilesList.Emplace(SpawnedTile);
	}
}

void AHexMap::SelectTile(AHexTile* Tile)
{
	switch (CurrentSelectionType)
	{
	case EHexSelectionType::Single:
	{
		for(AHexTile* PreviousTile : SelectedTiles)
		{
			PreviousTile->DeSelectTile();
		}
		SelectedTiles.Empty();

		if (Tile)
		{
			SelectedTiles.Add(Tile);
			Tile->SelectTile();
		}
		break;
	}
	case EHexSelectionType::Line:
	{
		for (AHexTile* PreviousTile : SelectedTiles)
		{
			PreviousTile->DeSelectTile();
		}
		SelectedTiles.Empty();

		if (Tile)
		{
			TArray<FHex> LineHexes = FHex::GetLine(FHex(0, 0), Tile->GetHex());
			for (const FHex& LineHex : LineHexes)
			{
				AHexTile* LineTile = GetTile(LineHex);
				if (LineTile)
				{
					LineTile->SelectTile();
					SelectedTiles.Emplace(LineTile);
				}
			}
		}
		break;
	}
	}
}

AHexTile* AHexMap::GetTile(const FHex& Coords)
{
	for (AHexTile* Tile : TilesList)
	{
		if (Tile->GetHex() == Coords)
		{
			return Tile;
		}
	}
	return nullptr;
}

// Called every frame
void AHexMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

