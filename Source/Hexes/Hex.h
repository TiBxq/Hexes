// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Hex.generated.h"

PRAGMA_DISABLE_OPTIMIZATION

struct FHexCube
{
	int32 q, r, s;

	FHexCube(int32 q_, int32 r_, int32 s_) : q(q_), r(r_), s(s_) {}

	//FHex ToHex() const { return FHex(q, r); }
};

struct FHexCubeFloat
{
	float q, r, s;

	FHexCubeFloat(float q_, float r_, float s_) : q(q_), r(r_), s(s_) {}

	FHexCubeFloat(const FHexCube& From) : q(From.q), r(From.r), s(From.s) {}

	FHexCube Round() const
	{
		float rounded_q = FMath::RoundToFloat(q);
		float rounded_r = FMath::RoundToFloat(r);
		float rounded_s = FMath::RoundToFloat(s);

		float diff_q = FMath::Abs(q - rounded_q);
		float diff_r = FMath::Abs(r - rounded_r);
		float diff_s = FMath::Abs(s - rounded_s);

		if (diff_q > diff_r && diff_q > diff_s)
			rounded_q = -rounded_r - rounded_s;
		else if (diff_r > diff_s)
			rounded_r = -rounded_q - rounded_s;
		else
			rounded_s = -rounded_q - rounded_r;

		return FHexCube(rounded_q, rounded_r, rounded_s);
	}

	FHexCubeFloat Lerp(const FHexCubeFloat& Other, float Alpha) const
	{
		return FHexCubeFloat(
			FMath::Lerp<float>(q, Other.q, Alpha),
			FMath::Lerp<float>(r, Other.r, Alpha),
			FMath::Lerp<float>(s, Other.s, Alpha)
		);
	}

	FHexCubeFloat Add(const FHexCubeFloat& Other)
	{
		return FHexCubeFloat(q + Other.q, r + Other.r, s + Other.s);
	}
};

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

	FHex(const FHex& Other) : FHex(Other.q, Other.r) {}

	bool operator==(const FHex& other) const
	{
		return q == other.q && r == other.r;
	}

	bool operator!=(const FHex& other) const
	{
		return q != other.q || r != other.r;
	}

	int32 GetS() const { return -q - r; }

	FHex Add(const FHex& other) const
	{
		return FHex(q + other.q, r + other.r);
	}

	FHex Subtract(const FHex& other) const
	{
		return FHex(q - other.q, r - other.r);
	}

	TPair<float, float> GetCoords(float HexSize) const
	{
		float x = HexSize * (3.f / 2.f * q);
		float y = HexSize * (FMath::Sqrt(3.f) / 2.f * q + FMath::Sqrt(3.f) * r);
		return TPair<float, float>(x, y);
	}

	int32 Distance(const FHex& other) const
	{
		FHex dif = Subtract(other);
		return (FMath::Abs(dif.q) + FMath::Abs(dif.r) + FMath::Abs(dif.GetS())) / 2;
	}

	FHexCube ToCube() const
	{
		return FHexCube(q, r, GetS());
	}

	static TArray<FHex> GetDirectionVectors()
	{
		static TArray<FHex> Directions = 
		{
			FHex(0, 1), FHex(1, 0), FHex(0, -1), FHex(-1, 0), FHex(1, -1), FHex(-1, 1)
		};
		return Directions;
	}

	static FHex GetDirection(int32 direction)
	{
		return GetDirectionVectors()[direction];
	}

	FHex GetNeighbor(int32 direction) const
	{
		return Add(GetDirection(direction));
	}

	TArray<FHex> GetHexesInRange(int32 Range) const
	{
		TArray<FHex> Result;
		for (int32 i = -Range; i <= Range; ++i)
		{
			int32 From = FMath::Max(-Range, -i - Range);
			int32 To   = FMath::Min(Range, -i + Range);
			for(int32 j = From; j <= To; ++j)
			{
				Result.Emplace(Add(FHex(i, j)));
			}
		}
		return Result;
	}

	TArray<FHex> GetReachableHexes(int32 Range, const TArray<FHex>& Obstacles)
	{
		TArray<FHex> Visited;
		TMap<int32, TArray<FHex>> Frontier;
		Frontier.Add(0, { *this });
		Visited.Add(*this);
		for(int32 k = 0; k < Range; ++k)
		{
			for (const FHex& CurrentHex : Frontier[k])
			{
				for (int32 i = 0; i < 6; ++i)
				{
					FHex NeighborHex = CurrentHex.GetNeighbor(i);
					if (!Visited.Contains(NeighborHex) && !Obstacles.Contains(NeighborHex))
					{
						TArray<FHex>& FrontierArray = Frontier.FindOrAdd(k + 1);
						FrontierArray.Add(NeighborHex);
						Visited.Add(NeighborHex);
					}
				}
			}
		}
		return Visited;
	}

	static TArray<FHex> FindPath(const FHex& Start, const FHex& End, const TArray<FHex>& Obstacles, const TArray<FHex>& Area);

	static TArray<FHex> GetLine(const FHex& Start, const FHex& End)
	{
		TArray<FHex> Result;
		int32 N = Start.Distance(End);

		FHexCubeFloat StartCube(Start.ToCube());
		FHexCubeFloat EndCube(End.ToCube());
		//EndCube = EndCube.Add(FHexCubeFloat(0.f, 10.f, 10.f));

		for (int32 i = 0; i <= N; ++i)
		{
			FHexCube HexCube = (StartCube.Lerp(EndCube, 1.f / N * i)).Round();
			Result.Add(FHex(HexCube.q, HexCube.r));
		}

		return Result;
	}
};

FORCEINLINE uint32 GetTypeHash(const FHex& Hex)
{
	uint32 Hash = FCrc::MemCrc32(&Hex, sizeof(FHex));
	return Hash;
}

PRAGMA_ENABLE_OPTIMIZATION