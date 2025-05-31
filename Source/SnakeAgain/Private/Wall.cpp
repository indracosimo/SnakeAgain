// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

AWall::AWall()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshForMesh(TEXT("/Game/SnakeAgain/Material/SM_Arena"));
	if (MeshForMesh.Succeeded())
	{
		Mesh->SetStaticMesh(MeshForMesh.Object);
		Mesh->SetRelativeScale3D(FVector(1) / MeshForMesh.Object->GetBoundingBox().GetSize());
	}


	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterial(TEXT("/Game/SnakeAgain/Material/M_Wall"));
	if (DefaultMaterial.Succeeded())
	{
		WallMaterial = DefaultMaterial.Object;
	}


	if (WallMaterial)
	{
		Mesh->SetMaterial(0, WallMaterial);
	}

}
