// Fill out your copyright notice in the Description page of Project Settings.

#include "KoTLT.h"
#include "KoMountCharacter.h"
#include "UnrealNetwork.h"

// Sets default values
AKoMountCharacter::AKoMountCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AKoMountCharacter::SetupMesh(ObjectInitializer);
	AKoMountCharacter::SetupCamera(ObjectInitializer);
	AKoMountCharacter::SetupMovement(ObjectInitializer);
}

void AKoMountCharacter::SetupMesh(const FObjectInitializer& ObjectInitializer)
{
	// setup mount mesh
	MountMeshComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mount Mesh"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("SkeletalMesh'/Game/Player/Mount/Ostrich/Mesh/ostrich.ostrich'"));
	MountMeshComponent->SetSkeletalMesh(MeshObj.Object);
	MountMeshComponent->AttachParent = GetCapsuleComponent();
	MountMeshComponent->SetRelativeRotation(FRotator(0, -90, 0));

	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("AnimBlueprint'/Game/Player/Mount/Ostrich/Blueprints/OstrichMountAnimBP.OstrichMountAnimBP'"));
	MountMeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	MountMeshComponent->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);

//	GetCapsuleComponent()->SetHiddenInGame(false);
	GetCapsuleComponent()->SetCapsuleHalfHeight(100);
	GetCapsuleComponent()->SetCapsuleRadius(90);
}

void AKoMountCharacter::SetupCamera(const FObjectInitializer& ObjectInitializer)
{
	// setup camera
	/* The spring component sits between the character and the camera and handles position and rotation of the camera we attach to this spring arm. */
	CameraBoomComp = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));

	/* Some defaults to start with, socket is the start and target is position of our camera. Tweakable in Blueprint. */
	CameraBoomComp->SocketOffset = FVector(0, 0, 75.0);
	CameraBoomComp->TargetOffset = FVector(0, 0, 0);
	CameraBoomComp->TargetArmLength = 1500.0;
	CameraBoomComp->bAbsoluteRotation = true;
//	CameraBoomComp->RelativeRotation = FRotator(0, 90, 0);

	/* Enabling this makes the camera stick on the character’s back. */
//	CameraBoomComp->bUsePawnControlRotation = true;
	CameraBoomComp->AttachParent = MountMeshComponent;

	/* Simple camera, attached to the spring arm to handle the rotation. */
	CameraComp = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	CameraComp->FieldOfView = 90;
	CameraComp->AttachParent = CameraBoomComp;
}

void AKoMountCharacter::SetupMovement(const FObjectInitializer& ObjectInitializer)
{

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 180, 0);
	GetCharacterMovement()->GravityScale = 2;
	GetCharacterMovement()->MaxAcceleration = 600;
	GetCharacterMovement()->BrakingFrictionFactor = 0;
	GetCharacterMovement()->Mass = 50;
	GetCharacterMovement()->GroundFriction = 0;
	GetCharacterMovement()->BrakingDecelerationWalking = 150;
	GetCharacterMovement()->JumpZVelocity = 400;
	GetCharacterMovement()->AirControl = 0.8;
//	GetCharacterMovement()->ConstrainDirectionToPlane(FVector(1, 0, 0));
	//GetCharacterMovement()->ConstrainNormalToPlane(FVector(1, 0, 0));

	JumpMaxHoldTime = 0.01;
}

// Called when the game starts or when spawned
void AKoMountCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Controller && Controller->IsLocalController())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "ere");
		SetActorRotation(Controller->GetControlRotation());
	}
}

// Called every frame
void AKoMountCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// check if character is braking
	 speed = GetCharacterMovement()->Velocity.Size();
	 float fAcceleration = GetCharacterMovement()->GetCurrentAcceleration().Y;

	if (speed > 400 && fAcceleration == 0 && fLastAccelerationValue != 0 && !bIsJumping)
	{
		SetIsBraking(true);
	}
	else if (fAcceleration != 0 && fLastAccelerationValue == 0 || bIsJumping )
	{
		SetIsBraking(false);
	}

	fLastAccelerationValue = fAcceleration;
}

bool AKoMountCharacter::IsInitiatedJump() const
{
	return bIsJumping;
}

void AKoMountCharacter::SetIsJumping(bool NewJumping)
{
	bIsJumping = NewJumping;

	if (Role < ROLE_Authority)
	{
		ServerSetIsJumping(NewJumping);
	}
	else {
//		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "Server: " + Controller->GetName());
	}
}

bool AKoMountCharacter::CanJumpInternal_Implementation() const
{
	return true;
}

void AKoMountCharacter::Landed(const FHitResult& Hit) 
{
	Super::Landed(Hit);
	SetIsJumping(false);
}

void AKoMountCharacter::ServerSetIsJumping_Implementation(bool NewJumping)
{
	SetIsJumping(NewJumping);
}

bool AKoMountCharacter::ServerSetIsJumping_Validate(bool NewJumping)
{
	return true;
}

void AKoMountCharacter::SetIsBraking(bool NewBraking)
{
	bIsBraking = NewBraking;

	if (Role < ROLE_Authority)
	{
		ServerSetIsBraking(NewBraking);
	}
}

void AKoMountCharacter::ServerSetIsBraking_Implementation(bool NewBraking)
{
	SetIsBraking(NewBraking);
}

bool AKoMountCharacter::ServerSetIsBraking_Validate(bool NewBraking)
{
	return true;
}

void AKoMountCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Value is already updated locally, skip in replication step
	DOREPLIFETIME_CONDITION(AKoMountCharacter, bIsJumping, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AKoMountCharacter, bIsBraking, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AKoMountCharacter, speed, COND_SkipOwner);

	// Replicate to every client, no special condition required
//	DOREPLIFETIME(ASCharacter, Health);
//	DOREPLIFETIME(ASCharacter, Stamina);
}
