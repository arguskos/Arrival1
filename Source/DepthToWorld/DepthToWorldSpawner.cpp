// Fill out your copyright notice in the Description page of Project Settings.


#include "DepthToWorldSpawner.h"

// Sets default values
ADepthToWorldSpawner::ADepthToWorldSpawner()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADepthToWorldSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADepthToWorldSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADepthToWorldSpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

