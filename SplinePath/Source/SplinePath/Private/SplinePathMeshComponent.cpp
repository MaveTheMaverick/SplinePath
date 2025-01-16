// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePathMeshComponent.h"
#include "Components/SplineComponent.h"

void USplinePathMeshComponent::SetRoll(float StartRoll, float EndRoll, bool bUpdateMesh)
{
	SetStartRoll(StartRoll, false);
	SetEndRoll(EndRoll, bUpdateMesh);
}

void USplinePathMeshComponent::SetRollDegrees(float StartRollDegrees, float EndRollDegrees, bool bUpdateMesh)
{
	SetRoll(FMath::DegreesToRadians(StartRollDegrees), FMath::DegreesToRadians(EndRollDegrees), bUpdateMesh);
}

void USplinePathMeshComponent::SetFromSplineInputKeys(const USplineComponent* SplineComponent, float InputKey1, float InputKey2, FVector2D PathScale, FVector2D PathOffset, bool bScaleSize, bool bScaleOffset)
{
	if (!SplineComponent)
		return;

	FVector2D PathScale2 = PathScale;
	FVector2D PathOffset2 = PathOffset;

	FVector location1, location2, tangent1, tangent2;

	//SplineComponent->GetLocationAndTangentAtSplinePoint(PointIndex1, location1, tangent1, ESplineCoordinateSpace::Local);
	FTransform transform1 = SplineComponent->GetTransformAtSplineInputKey(InputKey1, ESplineCoordinateSpace::Local, true);
	FTransform transform2 = SplineComponent->GetTransformAtSplineInputKey(InputKey2, ESplineCoordinateSpace::Local, true);
	SplineParams.StartPos = transform1.GetLocation();
	SplineParams.EndPos = transform2.GetLocation();
	SplineParams.StartRoll = transform1.Rotator().Roll;
	SplineParams.EndRoll = transform2.Rotator().Roll;

	if (bScaleSize)
	{
		PathScale.X *= transform1.GetScale3D().Y;
		PathScale.Y *= transform1.GetScale3D().Z;
		PathScale2.X *= transform2.GetScale3D().Y;
		PathScale2.Y *= transform2.GetScale3D().Z;
	}
	SplineParams.StartScale = PathScale;
	SplineParams.EndScale = PathScale2;


	SplineParams.StartTangent = SplineComponent->GetTangentAtSplineInputKey(InputKey1, ESplineCoordinateSpace::Local);
	SplineParams.EndTangent = SplineComponent->GetTangentAtSplineInputKey(InputKey2, ESplineCoordinateSpace::Local);

	//FVector up1 = transform1.GetRotation().RotateVector(FVector::UpVector);
	//FVector right1 = transform1.GetRotation().RotateVector(FVector::RightVector);
	if (bScaleOffset)
	{
		PathOffset.X *= transform1.GetScale3D().Y;
		PathOffset.Y *= transform1.GetScale3D().Z;
		PathOffset2.X *= transform2.GetScale3D().Y;
		PathOffset2.Y *= transform2.GetScale3D().Z;
	}
	SplineParams.StartOffset = PathOffset;
	SplineParams.EndOffset = PathOffset2;




	//SplineComponent->GetUpVectorAtSplineInputKey(inputKey1, ESplineCoordinateSpace::Local);
	//SplineComponent->GetTangentAtSplineInputKey()

	bMeshDirty = true;
	UpdateRenderStateAndCollision();
}

void USplinePathMeshComponent::SetFromSplinePoints(const USplineComponent* SplineComponent, int32 PointIndex1, int32 PointIndex2, FVector2D PathScale, FVector2D PathOffset, bool bScaleSize, bool bScaleOffset)
{
	if (!SplineComponent)
		return;

	SetFromSplineInputKeys(SplineComponent, SplineComponent->GetInputKeyValueAtSplinePoint(PointIndex1), SplineComponent->GetInputKeyValueAtSplinePoint(PointIndex2), PathScale, PathOffset, bScaleSize, bScaleOffset);
}

void USplinePathMeshComponent::SetFromSplinePointsAndPath(const USplineComponent* SplineComponent, int32 PointIndex1, int32 PointIndex2, const FPathMesh& SplineMeshPath)
{
	SetFromSplinePoints(SplineComponent, PointIndex1, PointIndex2, SplineMeshPath.PathScale, SplineMeshPath.PathOffset, SplineMeshPath.bScaleSize, SplineMeshPath.bScaleOffset);
}