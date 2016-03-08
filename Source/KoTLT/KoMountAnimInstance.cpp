// Fill out your copyright notice in the Description page of Project Settings.

#include "KoTLT.h"
#include "KoMountAnimInstance.h"
#include "UnrealNetwork.h"

void UKoMountAnimInstance::NextIdleIndex()
{
	idleCounter++;

	if (idleCounter > 5)
	{
		idleCounter = 0;
		idleIndex = FMath::RandRange(0, 2);
	}
	else
	{
		idleIndex = 0;
	}
}


void UKoMountAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerMountCharacter = Cast<AKoMountCharacter>(TryGetPawnOwner());
}

void UKoMountAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!OwnerMountCharacter)
	{
		return;
	}

	// update variables
	speed = OwnerMountCharacter->speed;
	bIsBraking = OwnerMountCharacter->bIsBraking;
	bIsInAir = OwnerMountCharacter->GetCharacterMovement()->IsFalling();
}

void UKoMountAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Value is already updated locally, skip in replication step
	DOREPLIFETIME_CONDITION(UKoMountAnimInstance, bIsInAir, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UKoMountAnimInstance, bIsBraking, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UKoMountAnimInstance, speed, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UKoMountAnimInstance, idleIndex, COND_SkipOwner);
}



