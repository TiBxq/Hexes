// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hex.h"
#include "HexMap.generated.h"

class AHexTile;

UCLASS()
class HEXESPLUGIN_API AHexMap : public AActor
{
public:
	GENERATED_BODY()
	
	AHexMap();

	UFUNCTION(BlueprintCallable)
	TArray<FHex> GenerateMap() const;

	UFUNCTION(BlueprintCallable)
	void SpawnMap(const TArray<FHex>& Source);

	virtual void SelectTile(AHexTile* Tile);

	AHexTile* GetTile(const FHex& Coords);

	TArray<FHex> GetObstacles() const;

	TArray<FHex> GetHexesList() { return HexesList; }

	TArray<AHexTile*> GetSelectedTiles() { return SelectedTiles; }

	void OnTileUpdated(AHexTile* UpdatedTile);

	UFUNCTION(BlueprintCallable)
	void MakeSelectedTilesObstacles();

	void ResetSelection();

	void SelectHexes(const TArray<FHex>& Hexes);

	UPROPERTY(VisibleAnywhere)
	int32 HexSize = 100;

	UPROPERTY(EditDefaultsOnly)
	int32 MapSize = 3;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHexTile> HexActorClass;

protected:
	TArray<FHex> HexesList;

	UPROPERTY()
	TArray<AHexTile*> TilesList;

	UPROPERTY()
	TArray<AHexTile*> SelectedTiles;
};
