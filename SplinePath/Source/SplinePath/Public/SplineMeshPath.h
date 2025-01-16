// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePathMeshComponent.h"
#include "SplineMeshPath.generated.h"

class USplineComponent;
class UCollisionProfile;

UCLASS()
class SPLINEPATH_API ASplineMeshPath : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* SplinePath;

	// Sets default values for this actor's properties
	ASplineMeshPath();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere)
	TArray<FPathMesh> PathMeshes;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USplinePathMeshComponent> SplineMeshComponentClass = USplinePathMeshComponent::StaticClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
