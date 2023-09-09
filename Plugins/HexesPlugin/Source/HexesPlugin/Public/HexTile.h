// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hex.h"
#include "InputCoreTypes.h"

#include "HexTile.generated.h"

class UStaticMeshComponent;
class AHexMap;

UENUM(BlueprintType)
enum class EHexTileType : uint8
{
	Default,
	Obstacle
};

UCLASS()
class HEXESPLUGIN_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexTile();

	FHex GetHex() const { return Hex; }

	void SetHex(const FHex& NewHex) { Hex = NewHex; }

	void SetMap(AHexMap* Map) { ParentMap = Map; }

	EHexTileType GetHexType() const { return TileType; }

	UFUNCTION(BlueprintCallable)
	void MakeObstacle();

	UFUNCTION(BlueprintImplementableEvent)
	void Init();

	UFUNCTION(BlueprintImplementableEvent)
	void SelectTile();

	UFUNCTION(BlueprintImplementableEvent)
	void DeSelectTile();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTileUpdated();

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EHexTileType TileType;

	UPROPERTY()
	AHexMap* ParentMap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
