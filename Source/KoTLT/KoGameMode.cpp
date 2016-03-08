// Fill out your copyright notice in the Description page of Project Settings.

#include "KoTLT.h"
#include "KoGameMode.h"
#include "KoPlayerController.h"
#include "KoMountCharacter.h"
#include "KoPlayerStart.h"

AKoGameMode::AKoGameMode()
{
	PlayerControllerClass = AKoPlayerController::StaticClass();
	DefaultPawnClass = AKoMountCharacter::StaticClass();
}

AActor* AKoGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AKoPlayerStart* Start = Cast<AKoPlayerStart>(*It);

		if (Start && !Start->isInUse)
		{
			Start->SetInUse(true);
			Player->AddActorWorldRotation(Start->GetActorRotation());
			return Start;
		}
	}

	return NULL;
}


