// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexes/Hex.h"
#include "HexTile.generated.h"

class UStaticMeshComponent;
class AHexMap;

UCLASS()
class HEXES_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexTile();

	FHex GetHex() const { return Hex; }

	void SetHex(const FHex& NewHex) { Hex = NewHex; }

	void SetMap(AHexMap* Map) { ParentMap = Map; }

	UFUNCTION(BlueprintImplementableEvent)
	void Init();

	UFUNCTION(BlueprintImplementableEvent)
	void SelectTile();

	UFUNCTION(BlueprintImplementableEvent)
	void DeSelectTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTileClicked(AActor* TouchedActor, FKey ButtonPressed);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TileMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FHex Hex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* MaterialClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* Material;

	UPROPERTY()
	AHexMap* ParentMap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
