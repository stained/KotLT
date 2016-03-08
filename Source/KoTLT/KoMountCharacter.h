// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "KoPlayerController.h"
#include "KoMountCharacter.generated.h"

UCLASS()
class KOTLT_API AKoMountCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

private:
	/* Boom to handle distance to player mesh. */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* CameraBoomComp;

	/* Primary camera of the player*/
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* CameraComp;

	/* Default mesh of mount character */
	UPROPERTY(VisibleAnywhere, Category = "Character")
		USkeletalMeshComponent* MountMeshComponent;

	void SetupMesh(const FObjectInitializer& ObjectInitializer);
	void SetupCamera(const FObjectInitializer& ObjectInitializer);
	void SetupMovement(const FObjectInitializer& ObjectInitializer);

	float fLastAccelerationValue;

protected:
	virtual bool CanJumpInternal_Implementation() const override;

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
		
	/************************************************************************/
	/* Movement                                                             */
	/************************************************************************/

	/* Is character currently performing a jump action. Resets on landed.  */
	UPROPERTY(Transient, Replicated)
		bool bIsJumping;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsInitiatedJump() const;

	void SetIsJumping(bool NewJumping);
	void Landed(const FHitResult& Hit) override;

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetIsJumping(bool NewJumping);

	UPROPERTY(Transient, Replicated)
		float speed;

	UPROPERTY(Transient, Replicated)
		bool bIsBraking;

	void SetIsBraking(bool NewBraking);

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetIsBraking(bool NewBraking);
};
