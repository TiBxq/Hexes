// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestHexMap.generated.h"

class UHexMap;
class AHexPawn;
class AHexTile;

UENUM(BlueprintType)
enum class EHexSelectionType : uint8
{
	Single,
	Line,
	Range,
	RangeReachable,
	FindPath,
	SendPath
};

UCLASS()
class HEXES_API ATestHexMap : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestHexMap();

	UFUNCTION(BlueprintCallable)
	void SpawnTestPawn();

	UFUNCTION(BlueprintCallable)
	void SetSelectionType(EHexSelectionType NewType) { CurrentSelectionType = NewType; }

	void SelectTile(AHexTile* Tile);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHexPawn> TestPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHexMap> HexMapClass;

protected:
	UPROPERTY(BlueprintReadOnly)
	UHexMap* HexMap;

	UPROPERTY(BlueprintReadOnly)
	AHexPawn* TestPawn;

	EHexSelectionType CurrentSelectionType;
};
