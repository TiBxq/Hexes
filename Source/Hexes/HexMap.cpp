// Fill out your copyright notice in the Description page of Project Settings.


#include "HexMap.h"
#include "Hexes/HexTile.h"

// Sets default values
AHexMap::AHexMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectedTile = nullptr;
}

// Called when the game starts or when spawned
void AHexMap::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHexMap::GenerateMap()
{
	FHex ZeroHex(0, 0);
	HexesList.Add(ZeroHex);

	for (int32 k = 0; k < MapSize; ++k)
	{
		TArray<FHex> HexesToAdd;
		for (const FHex& Hex : HexesList)
		{
			for (int32 i = 0; i < 6; ++i)
			{
				FHex NewHex = Hex.GetNeighbor(i);
				if (!HexesList.Contains(NewHex) && !HexesToAdd.Contains(NewHex))
				{
					HexesToAdd.Add(NewHex);
				}
			}
		}

		for (const FHex& Hex : HexesToAdd)
		{
			HexesList.Add(Hex);
		}
	}
}

void AHexMap::SpawnMap()
{
	for (const FHex& Hex : HexesList)
	{
		float x = HexSize * (3.f / 2.f * Hex.q);
		float y = HexSize * (FMath::Sqrt(3.f) / 2.f * Hex.q + FMath::Sqrt(3.f) * Hex.r);
		FVector Position(x, y, 0.f);

		FActorSpawnParameters Params;
		AHexTile* SpawnedTile = GetWorld()->SpawnActor<AHexTile>(HexActorClass, Position, FRotator(0.f), Params);
		if (SpawnedTile)
		{
			SpawnedTile->SetHex(Hex);
			SpawnedTile->Init();
		}
	}
}

// Called every frame
void AHexMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

