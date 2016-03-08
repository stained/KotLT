// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "KoMountCharacter.h"
#include "KoMountAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class KOTLT_API UKoMountAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	uint8 idleCounter;


public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void NextIdleIndex();

	UPROPERTY(Transient, Replicated, BlueprintReadWrite, EditAnywhere, Category = "Movement")
		bool bIsInAir;

	UPROPERTY(Transient, Replicated, BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float speed;

	UPROPERTY(Transient, Replicated, BlueprintReadWrite, EditAnywhere, Category = "Movement")
		int32 idleIndex;

	UPROPERTY(Transient, Replicated, BlueprintReadWrite, EditAnywhere, Category = "Movement")
		bool bIsBraking;

	AKoMountCharacter *OwnerMountCharacter;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
};
