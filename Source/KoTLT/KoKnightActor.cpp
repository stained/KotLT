// Fill out your copyright notice in the Description page of Project Settings.

#include "KoTLT.h"
#include "KoKnightActor.h"


// Sets default values
AKoKnightActor::AKoKnightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKoKnightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKoKnightActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

