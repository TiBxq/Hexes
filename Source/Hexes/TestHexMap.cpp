// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHexMap.h"
#include "HexMap.h"
#include "HexPawn.h"
#include "HexTile.h"

ATestHexMap::ATestHexMap()
{
	PrimaryActorTick.bCanEverTick = true;

	HexMap = CreateDefaultSubobject<UHexMap>(TEXT("HexMap"));
	CurrentSelectionType = EHexSelectionType::RangeReachable;
}

void ATestHexMap::SpawnTestPawn()
{
	FVector Position(0.f, 0.f, 100.f);
	FActorSpawnParameters Params;
	TestPawn = GetWorld()->SpawnActor<AHexPawn>(TestPawnClass, Position, FRotator(0.f), Params);
}

void ATestHexMap::SelectTile(AHexTile* Tile)
{
	switch (CurrentSelectionType)
	{
	case EHexSelectionType::Single:
	{
		HexMap->ResetSelection();

		if (Tile)
		{
			HexMap->GetSelectedTiles().Add(Tile);
			Tile->SelectTile();
		}
		break;
	}
	case EHexSelectionType::Line:
	{
		HexMap->ResetSelection();
		if (Tile)
		{
			TArray<FHex> LineHexes = FHex::GetLine(FHex(0, 0), Tile->GetHex());
			HexMap->SelectHexes(MoveTemp(LineHexes));
		}
		break;
	}
	case EHexSelectionType::Range:
	{
		HexMap->ResetSelection();
		if (Tile)
		{
			TArray<FHex> RangedHexes = Tile->GetHex().GetHexesInRange(2);
			HexMap->SelectHexes(MoveTemp(RangedHexes));
		}
		break;
	}
	case EHexSelectionType::RangeReachable:
	{
		HexMap->ResetSelection();
		if (Tile && Tile->GetHexType() != EHexTileType::Obstacle)
		{
			TArray<FHex> RangedHexes = Tile->GetHex().GetReachableHexes(2, HexMap->GetObstacles());
			HexMap->SelectHexes(MoveTemp(RangedHexes));
		}
		break;
	}
	case EHexSelectionType::FindPath:
	{
		HexMap->ResetSelection();
		if (Tile && Tile->GetHexType() != EHexTileType::Obstacle)
		{
			TArray<FHex> PathHexes = FHex::FindPath(FHex(0, 0), Tile->GetHex(), HexMap->GetObstacles(), HexMap->GetHexesList());
			HexMap->SelectHexes(MoveTemp(PathHexes));
		}
		break;
	}
	case EHexSelectionType::SendPath:
	{
		HexMap->ResetSelection();
		if (Tile && Tile->GetHexType() != EHexTileType::Obstacle)
		{
			TArray<FHex> PathHexes = FHex::FindPath(FHex(0, 0), Tile->GetHex(), HexMap->GetObstacles(), HexMap->GetHexesList());
			if (TestPawn)
			{
				TestPawn->SetPath(PathHexes);
				TestPawn->StartMove();
			}
		}
		break;
	}
	}
}