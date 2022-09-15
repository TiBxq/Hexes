// Fill out your copyright notice in the Description page of Project Settings.


#include "Hex.h"

TArray<FHex> FHex::FindPath(const FHex& Start, const FHex& End)
{
	bool Found = false;
	TArray<FHex> Path;

	TArray<FHex> Frontier;
	TMap<FHex, FHex> CameFrom;

	Frontier.Add(Start);

	while (Frontier.Num() > 0)
	{
		FHex CurrentHex = Frontier.Pop();
		if (CurrentHex == End)
		{
			Found = true;
			break;
		}

		for (int32 i = 0; i < 6; ++i)
		{
			FHex NeighborHex = CurrentHex.GetNeighbor(i);
			if (!CameFrom.Contains(NeighborHex))
			{
				CameFrom[NeighborHex] = CurrentHex;
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