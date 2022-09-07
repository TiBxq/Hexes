// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexes/Hex.h"
#include "HexTile.generated.h"

class UStaticMeshComponent;

UCLASS()
class HEXES_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexTile();

	FHex GetHex() const { return Hex; }

	void SetHex(const FHex& NewHex) { Hex = NewHex; }

	UFUNCTION(BlueprintImplementableEvent)
	void Init();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TileMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FHex Hex;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
