// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalAIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



void AFinalAIController::BeginPlay()
{
Super::BeginPlay();

UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), waypoints);

GoToRandomWaypoint();
}


void AFinalAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	GetWorldTimerManager().SetTimer(timerHandle, this, &AFinalAIController::GoToRandomWaypoint, 2.0f, false);
}

ATargetPoint* AFinalAIController::GetRandomWaypoint()
{
	auto index = FMath::RandRange(0, waypoints.Num() - 1);
	return Cast<ATargetPoint>(waypoints[index]);

}


void AFinalAIController::GoToRandomWaypoint()
{
	MoveToActor(GetRandomWaypoint(),1.0f,false,true,false,0,true);
}
