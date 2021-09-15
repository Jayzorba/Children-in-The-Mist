// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "CharacterController.generated.h"

UCLASS()
class LOST2_API ACharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//array of areas that the player is currently in.
	TArray<AActor*> SanityVolumes;


private:
	//functions for movement
	void HorizontalMovement(float value);
	void VerticalMovement(float value);

	//functions for rotation
	void HorizontalRotation(float value);
	void VerticalRotation(float value);

	//functions to update and check sanity
	void CheckSanity();
	void UpdateSanity();

	//functions to update post processing
	void ChangeCamera();
	void UpdateFringeIntensity();
	void CheckFringeIntensity();
	void UpdateVignette();
	void CheckVignette();


	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* cam;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShake> MyShake;

	//sanity settings
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float sanity;
	
	float rateOfSanity;

	//fringe settings (Colour Blur)
	float fringeIntensity;
	float maxFringe;
	float minFringe;
	float rateOfIntensity;

	//vignette settings (Darkness around edges)
	float vignetteIntensity;
	float maxVignette;
	float minVignette;
	float rateOfVignette;


};
