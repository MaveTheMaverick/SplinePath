// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineMeshPath.h"
#include "Components/SplineComponent.h"


// Sets default values
ASplineMeshPath::ASplineMeshPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = SplinePath;
}

void ASplineMeshPath::OnConstruction(const FTransform& Transform)
{
	for (auto& pathMesh : PathMeshes)
	{
		if (pathMesh.Mesh->IsValidLowLevelFast())
		{
			const int32 lastSplinePathIndex = SplinePath->GetNumberOfSplinePoints() - 1;

			for (int32 i = 0; i < lastSplinePathIndex - 1; i++)
			{
				USplinePathMeshComponent* splineMeshComponent = Cast<USplinePathMeshComponent>(AddComponentByClass(SplineMeshComponentClass, false, FTransform::Identity, false));
				splineMeshComponent->SetStaticMesh(pathMesh.Mesh);

				//Push override materials
				for (int32 j = 0; j < pathMesh.OverrideMaterials.Num(); j++)
				{
					if (pathMesh.OverrideMaterials[j])	//Prevent unwanted behavior where an empty array index might remove existing materials
						splineMeshComponent->SetMaterial(j, pathMesh.OverrideMaterials[j]);
				}

				splineMeshComponent->SetFromSplinePointsAndPath(SplinePath, i, i + 1, pathMesh);
			}

		}
	}
}

// Called when the game starts or when spawned
void ASplineMeshPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplineMeshPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

