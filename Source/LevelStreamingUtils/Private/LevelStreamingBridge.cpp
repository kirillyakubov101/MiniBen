// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamingBridge.h"

// Sets default values
ALevelStreamingBridge::ALevelStreamingBridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelStreamingBridge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelStreamingBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

