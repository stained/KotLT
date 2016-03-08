// Fill out your copyright notice in the Description page of Project Settings.

#include "KoTLT.h"
#include "KoPlayerController.h"
#include "KoMountCharacter.h"

// Called to bind functionality to input
void AKoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveRight", this, &AKoPlayerController::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AKoPlayerController::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AKoPlayerController::OnStopJump);
}

void AKoPlayerController::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		// constrained direction in y axis
		const FVector Direction = FRotationMatrix(FRotator(0, -1, 0)).GetScaledAxis(EAxis::Y);
		GetCharacter()->AddMovementInput(Direction, Val);
	}
}

void AKoPlayerController::OnStartJump()
{
	AKoMountCharacter* character = Cast<AKoMountCharacter>(GetCharacter());
	character->bPressedJump = true;
	character->SetIsJumping(true);
}


void AKoPlayerController::OnStopJump()
{
	AKoMountCharacter* character = Cast<AKoMountCharacter>(GetCharacter());
	character->bPressedJump = true;
}
