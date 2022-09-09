// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hex.h"
#include "HexMap.generated.h"

class AHexTile;

UCLASS()
class HEXES_API AHexMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexMap();

	UFUNCTION(BlueprintCallable)
	void GenerateMap();

	UFUNCTION(BlueprintCallable)
	void SpawnMap();

	void SelectTile(AHexTile* Tile) { SelectedTile = Tile; }

	UPROPERTY(VisibleAnywhere)
	int32 HexSize = 100;

	UPROPERTY(EditDefaultsOnly)
	int32 MapSize = 3;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHexTile> HexActorClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FHex> HexesList;

	UPROPERTY()
	AHexTile* SelectedTile;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
