// Fill out your copyright notice in the Description page of Project Settings.


#include "HexMap.h"
#include "HexTile.h"

//PRAGMA_DISABLE_OPTIMIZATION

UHexMap::UHexMap()
{
}

TArray<FHex> UHexMap::GenerateMap() const
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

void UHexMap::SpawnMap(const TArray<FHex>& Source)
{
	TilesList.Empty();
	HexesList = Source;
	for (const FHex& Hex : Source)
	{
		TPair<float, float> Coords = Hex.GetCoords(HexSize);
		FVector Position(Coords.Key, Coords.Value, 0.f);

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

void UHexMap::SelectTile(AHexTile* Tile)
{
}

AHexTile* UHexMap::GetTile(const FHex& Coords)
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

TArray<FHex> UHexMap::GetObstacles() const
{
	TArray<FHex> Result;
	for (const AHexTile* Tile : TilesList)
	{
		if (Tile->GetHexType() == EHexTileType::Obstacle)
		{
			Result.Emplace(Tile->GetHex());
		}
	}
	return Result;
}

void UHexMap::OnTileUpdated(AHexTile* UpdatedTile)
{

}

void UHexMap::MakeSelectedTilesObstacles()
{
	for (AHexTile* Tile : SelectedTiles)
	{
		Tile->MakeObstacle();
	}
}

void UHexMap::ResetSelection()
{
	for (AHexTile* PreviousTile : SelectedTiles)
	{
		PreviousTile->DeSelectTile();
	}
	SelectedTiles.Empty();
}

void UHexMap::SelectHexes(const TArray<FHex>& Hexes)
{
	for (const FHex& Hex : Hexes)
	{
		if (AHexTile* RangedTile = GetTile(Hex))
		{
			RangedTile->SelectTile();
			SelectedTiles.Emplace(RangedTile);
		}
	}
}

//PRAGMA_ENABLE_OPTIMIZATION