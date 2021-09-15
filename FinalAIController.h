// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FinalAIController.generated.h"

/**
 * 
 */
UCLASS()
class LOST2_API AFinalAIController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
private:
	UPROPERTY()
		TArray<AActor*> waypoints;
	UFUNCTION()
		ATargetPoint* GetRandomWaypoint();
	UFUNCTION()
		void GoToRandomWaypoint();

	FTimerHandle timerHandle;
};