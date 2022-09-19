// Fill out your copyright notice in the Description page of Project Settings.


#include "Hex.h"

TArray<FHex> FHex::FindPath(const FHex& Start, const FHex& End, const TArray<FHex>& Obstacles, const TArray<FHex>& Area)
{
	bool Found = false;
	TArray<FHex> Path;

	TArray<FHex> Frontier;
	TMap<FHex, FHex> CameFrom;

	Frontier.Emplace(Start);
	CameFrom.Emplace(Start, Start);

	while (Frontier.Num() > 0)
	{
		FHex CurrentHex = Frontier[0];
		Frontier.RemoveAt(0);
		if (CurrentHex == End)
		{
			Found = true;
			break;
		}

		for (int32 i = 0; i < 6; ++i)
		{
			FHex NeighborHex = CurrentHex.GetNeighbor(i);
			if (Area.Contains(NeighborHex) && !CameFrom.Contains(NeighborHex) && !Obstacles.Contains(NeighborHex))
			{
				CameFrom.Emplace(NeighborHex, CurrentHex);
				Frontier.Emplace(MoveTemp(NeighborHex));
			}
		}
	}

	if (Found)
	{
		FHex CurrentHex = End;
		while (CurrentHex != Start)
		{
			Path.Add(CurrentHex);
			CurrentHex = CameFrom[CurrentHex];
		}
		Path.Add(CurrentHex);
	}

	return Path;
}