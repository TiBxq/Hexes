// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexMap.h"
#include "TestHexMap.generated.h"

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
class HEXES_API ATestHexMap : public AHexMap
{
	GENERATED_BODY()
	
public:	
	ATestHexMap();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnTestPawn();

	UFUNCTION(BlueprintCallable)
	void SetSelectionType(EHexSelectionType NewType) { CurrentSelectionType = NewType; }

	void SelectTile(AHexTile* Tile);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHexPawn> TestPawnClass;

protected:
	UPROPERTY(BlueprintReadOnly)
	AHexPawn* TestPawn;

	EHexSelectionType CurrentSelectionType;
};
