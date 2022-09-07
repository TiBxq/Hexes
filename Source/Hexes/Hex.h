// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Hex.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct HEXES_API FHex
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 q;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 r;

	int32 GetS() const { return -q - r; }
};
