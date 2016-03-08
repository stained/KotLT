// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerStart.h"
#include "KoPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class KOTLT_API AKoPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Actor")
		bool isInUse;

	UFUNCTION(BlueprintCallable, Category = "Actor")
		void SetInUse(bool inUse);

};
