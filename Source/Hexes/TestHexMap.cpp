// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHexMap.h"
#include "HexMap.h"
#include "HexPawn.h"
#include "HexTile.h"

ATestHexMap::ATestHexMap()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentSelectionType = EHexSelectionType::RangeReachable;
}

void ATestHexMap::BeginPlay()
{
	Super::BeginPlay();
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
		ResetSelection();

		if (Tile)
		{
			GetSelectedTiles().Add(Tile);
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
			TArray<FHex> PathHexes = FHex::FindPath(FHex(0, 0), Tile->GetHex(), GetObstacles(), GetHexesList());
			SelectHexes(MoveTemp(PathHexes));
		}
		break;
	}
	case EHexSelectionType::SendPath:
	{
		ResetSelection();
		if (Tile && Tile->GetHexType() != EHexTileType::Obstacle)
		{
			TArray<FHex> PathHexes = FHex::FindPath(FHex(0, 0), Tile->GetHex(), GetObstacles(), GetHexesList());
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