// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hex.h"
#include "HexMap.generated.h"

class AHexTile;

UENUM(BlueprintType)
enum class EHexSelectionType : uint8
{
	Single,
	Line,
	Range
};

UCLASS()
class HEXES_API AHexMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexMap();

	UFUNCTION(BlueprintCallable)
	TArray<FHex> GenerateMap() const;

	UFUNCTION(BlueprintCallable)
	void SpawnMap(const TArray<FHex>& Source);

	void SelectTile(AHexTile* Tile);

	AHexTile* GetTile(const FHex& Coords);

	UPROPERTY(VisibleAnywhere)
	int32 HexSize = 100;

	UPROPERTY(EditDefaultsOnly)
	int32 MapSize = 3;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHexTile> HexActorClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetSelection();

	void SelectHexes(const TArray<FHex>& Hexes);

	EHexSelectionType CurrentSelectionType;

	TArray<FHex> HexesList;

	UPROPERTY()
	TArray<AHexTile*> TilesList;

	UPROPERTY()
	TArray<AHexTile*> SelectedTiles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
