// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

// Sets default values
ACharacterController::ACharacterController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//receive input
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//controller Rotation Yaw automatically set to true so set to fals
	bUseControllerRotationYaw = false;

	//setup cam
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->AttachTo(RootComponent);
	cam->SetRelativeLocation(FVector(0, 0, 80));

	//Sanity initialisers
	sanity = 100.0f;
	rateOfSanity = -5.0f;

	//post processing initialisers
	fringeIntensity = 0.0f;
	maxFringe = 20.0f;
	minFringe = 0.0f;
	vignetteIntensity = 0.0f;
	maxVignette = 1.0f;
	minVignette = 0.0f;
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//updates and checks to sanity and camera post processing variables
	UpdateSanity();
	UpdateFringeIntensity();
	UpdateVignette();
	CheckSanity();
	CheckFringeIntensity();
	CheckVignette();
	ChangeCamera();

	//Changes sanity, and post processing intensity
	sanity += rateOfSanity * DeltaTime;
	fringeIntensity += rateOfIntensity * DeltaTime;
	vignetteIntensity += rateOfVignette * DeltaTime;

	//DEBUG:
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-10, 1.0f, FColor::Yellow, FString::Printf(TEXT("Sanity = %f"), sanity));
	//	GEngine->AddOnScreenDebugMessage(-10, 3.0f, FColor::Green, FString::Printf(TEXT("intensity = %f"), fringeIntensity));
	//}


}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &ACharacterController::HorizontalMovement);
	InputComponent->BindAxis("Vertical", this, &ACharacterController::VerticalMovement);

	InputComponent->BindAxis("HorizontalRotation", this, &ACharacterController::HorizontalRotation);
	InputComponent->BindAxis("VerticalRotation", this, &ACharacterController::VerticalRotation);
}

void ACharacterController::HorizontalMovement(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ACharacterController::VerticalMovement(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ACharacterController::HorizontalRotation(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void ACharacterController::VerticalRotation(float value)
{
	if (value)
	{
		float temp = cam->GetRelativeRotation().Pitch + value;
		if (temp<65 && temp>-65)
		{
			cam->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void ACharacterController::CheckSanity()
{

	if (sanity < 0)
	{
		sanity = 0.1f;
	}

	else if (sanity > 100.0f)
	{
		sanity = 100.0f;
	}
}

void ACharacterController::UpdateSanity()
{

	if (SanityVolumes.Num() > 0)
	{
		rateOfSanity = -10.f;
	}
	else
	{
		rateOfSanity = 10.0f;
	}
}


void ACharacterController::UpdateFringeIntensity()
{
	if (SanityVolumes.Num() > 0)
	{
		rateOfIntensity = 3.0f;
	}
	else
	{
		rateOfIntensity = -3.0f;
	}
}

void ACharacterController::CheckFringeIntensity()
{

	if (fringeIntensity < minFringe)
	{
		fringeIntensity = 0.1f;
	}

	else if (fringeIntensity > maxFringe)
	{
		fringeIntensity = 20.0f;
	}
}

void ACharacterController::UpdateVignette()
{
	if (SanityVolumes.Num() > 0)
	{
		rateOfVignette = .2f;
	}
	else
	{
		rateOfVignette = -.2f;
	}
}

void ACharacterController::CheckVignette()
{
	if (vignetteIntensity < minVignette)
	{
		vignetteIntensity = 0.1f;
	}

	else if (vignetteIntensity > maxVignette)
	{
		vignetteIntensity = 1.0f;
	}
}

void ACharacterController::ChangeCamera()
{

	cam->PostProcessSettings.bOverride_BloomIntensity = true;
	cam->PostProcessSettings.bOverride_DepthOfFieldFocalRegion = true;
	cam->PostProcessSettings.bOverride_ColorSaturation = true;
	cam->PostProcessSettings.bOverride_SceneFringeIntensity = true;
	cam->PostProcessSettings.bOverride_VignetteIntensity = true;

	//cam->PostProcessSettings.BloomIntensity = sanity / 20;
	cam->PostProcessSettings.DepthOfFieldFocalRegion = sanity * 10.0f;
	cam->PostProcessSettings.SceneFringeIntensity = fringeIntensity;
	cam->PostProcessSettings.VignetteIntensity = vignetteIntensity;


}

