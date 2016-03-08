// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "KoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KOTLT_API AKoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AKoGameMode();

	AActor* AKoGameMode::ChoosePlayerStart_Implementation(AController* Player) override;
};
