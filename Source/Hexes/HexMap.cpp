// Fill out your copyright notice in the Description page of Project Settings.


#include "HexMap.h"
#include "Hexes/HexTile.h"
#include "Hexes/HexPawn.h"

// Sets default values
AHexMap::AHexMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentSelectionType = EHexSelectionType::RangeReachable;
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

void AHexMap::SpawnTestPawn()
{
	FVector Position(0.f);
	FActorSpawnParameters Params;
	TestPawn = GetWorld()->SpawnActor<AHexPawn>(TestPawnClass, Position, FRotator(0.f), Params);
}

void AHexMap::SelectTile(AHexTile* Tile)
{
	switch (CurrentSelectionType)
	{
	case EHexSelectionType::Single:
	{
		ResetSelection();

		if (Tile)
		{
			SelectedTiles.Add(Tile);
			Tile->SelectTile();
		}
		break;
	}
	case EHexSelectionType::Line:
	{
		ResetSelection();
		if (Tile)
		{
			TArray<FHex> LineHexes = FHex::GetLine(FHex(0, 0), Tile->GetHex());
			SelectHexes(MoveTemp(LineHexes));
		}
		break;
	}
	case EHexSelectionType::Range:
	{
		ResetSelection();
		if (Tile)
		{
			TArray<FHex> RangedHexes = Tile->GetHex().GetHexesInRange(2);
			SelectHexes(MoveTemp(RangedHexes));
		}
		break;
	}
	case EHexSelectionType::RangeReachable:
	{
		ResetSelection();
		if (Tile && Tile->GetHexType() != EHexTileType::Obstacle)
		{
			TArray<FHex> RangedHexes = Tile->GetHex().GetReachableHexes(2, GetObstacles());
			SelectHexes(MoveTemp(RangedHexes));
		}
		break;
	}
	case EHexSelectionType::FindPath:
	{
		ResetSelection();
		if (Tile && Tile->GetHexType() != EHexTileType::Obstacle)
		{
			TArray<FHex> PathHexes = FHex::FindPath(FHex(0, 0), Tile->GetHex(), GetObstacles(), HexesList);
			SelectHexes(MoveTemp(PathHexes));
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

TArray<FHex> AHexMap::GetObstacles() const
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

void AHexMap::OnTileUpdated(AHexTile* UpdatedTile)
{

}

void AHexMap::MakeSelectedTilesObstacles()
{
	for (AHexTile* Tile : SelectedTiles)
	{
		Tile->MakeObstacle();
	}
}

void AHexMap::ResetSelection()
{
	for (AHexTile* PreviousTile : SelectedTiles)
	{
		PreviousTile->DeSelectTile();
	}
	SelectedTiles.Empty();
}

void AHexMap::SelectHexes(const TArray<FHex>& Hexes)
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

// Called every frame
void AHexMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

