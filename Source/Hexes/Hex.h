// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Hex.generated.h"

/**
 * 
 */
USTRUCT()
struct HEXES_API FHex
{
	GENERATED_BODY()
	
	int32 q;
	int32 r;

	int32 GetS() const { return -q - r; }
};
