// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "KoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KOTLT_API AKoPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	

public:
		// Called to bind functionality to input
		virtual void SetupInputComponent() override;


		/************************************************************************/
		/* Movement                                                             */
		/************************************************************************/

		void MoveRight(float Val);

		/* Client mapped to Input */
		void OnStartJump();

		/* Client mapped to Input */
		void OnStopJump();
};
