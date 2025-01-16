// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineMeshComponent.h"
#include "SplinePathMeshComponent.generated.h"

//Useful data for spline meshes and static meshes that follow paths
USTRUCT(BlueprintType)
struct FPathMesh
{
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(BlueprintReadOnly)
	//TArray<UPonyExpressSplineMeshComponent*> SplineMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UMaterial>> OverrideMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCollisionProfile* CollisionProfile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector2D PathScale = { 1,1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector2D PathOffset = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	bool bScaleSize = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	bool bScaleOffset = true;

	//Goes point to point if set to 0.0
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TilingLength = 0.0f;
};

USTRUCT(BlueprintType)
struct FPathMeshAdvanced : public FPathMesh
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector2D PathScaleVariation = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector2D PathOffsetVariation = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FRotator PathRotationVariation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSnapToGround = false;
};

/**
 * 
 */
UCLASS()
class SPLINEPATH_API USplinePathMeshComponent : public USplineMeshComponent
{
	GENERATED_BODY()
public:
	/** Set the start and end roll, in radians */
	UFUNCTION(BlueprintCallable, Category = SplineMesh, meta = (DisplayName = "Set Roll Radians"))
	void SetRoll(float StartRoll, float EndRoll, bool bUpdateMesh = true);

	/** Set the start and end roll in degrees */
	UFUNCTION(BlueprintCallable, Category = SplineMesh)
	void SetRollDegrees(float StartRollDegrees, float EndRollDegrees, bool bUpdateMesh = true);

	//Make the spline mesh follow a spline component
	UFUNCTION(BlueprintCallable, Category = SplineMesh)
	void SetFromSplineInputKeys(const USplineComponent* SplineComponent, float InputKey1, float InputKey2, FVector2D PathScale = FVector2D::UnitVector, FVector2D PathOffset = FVector2D::ZeroVector, bool bScaleSize = true, bool bScaleOffset = true);

	//Make the spline mesh follow a spline component
	UFUNCTION(BlueprintCallable, Category = SplineMesh)
	void SetFromSplinePoints(const USplineComponent* SplineComponent, int32 PointIndex1, int32 PointIndex2, FVector2D PathScale = FVector2D::UnitVector, FVector2D PathOffset = FVector2D::ZeroVector, bool bScaleSize = true, bool bScaleOffset = true);

	//Make the spline mesh follow a spline component. Takes it's transform settings from a FPathMesh
	UFUNCTION(BlueprintCallable, Category = SplineMesh)
	void SetFromSplinePointsAndPath(const USplineComponent* SplineComponent, int32 PointIndex1, int32 PointIndex2, const FPathMesh& SplineMeshPath);
	
};
