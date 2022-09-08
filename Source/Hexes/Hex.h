// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Hex.generated.h"

USTRUCT(BlueprintType)
struct HEXES_API FHex
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 q;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 r;

	FHex() : q(0), r(0) {}

	FHex(int32 new_q, int32 new_r)
	{
		q = new_q;
		r = new_r;
	}

	bool operator==(const FHex& other) const
	{
		return q == other.q && r == other.r;
	}

	int32 GetS() const { return -q - r; }

	FHex Add(const FHex& other) const
	{
		return FHex(q + other.q, r + other.r);
	}

	static TArray<FHex> GetDirectionVectors()
	{
		static TArray<FHex> Directions = 
		{
			FHex(0, 1), FHex(1, 0), FHex(0, -1), FHex(-1, 0), FHex(1, -1), FHex(-1, 1)
		};
		return Directions;
	}

	FHex GetDirection(int32 direction) const
	{
		return GetDirectionVectors()[direction];
	}

	FHex GetNeighbor(int32 direction) const
	{
		return Add(GetDirection(direction));
	}
};
