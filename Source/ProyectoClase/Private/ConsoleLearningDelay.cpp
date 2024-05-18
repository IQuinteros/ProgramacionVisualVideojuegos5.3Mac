// Docente Ignacio Quinteros


#include "ConsoleLearningDelay.h"

#include "ConsoleLearningSubsystem.h"

UConsoleLearningDelay* UConsoleLearningDelay::LearningDelay(const UObject* WorldContextObject, const float DelayTime)
{
	UConsoleLearningDelay* BlueprintNode = NewObject<UConsoleLearningDelay>();
	BlueprintNode->WorldContextObject = WorldContextObject;
	BlueprintNode->DelayTime = DelayTime;
	return BlueprintNode;
}

void UConsoleLearningDelay::Activate()
{
	Super::Activate();
	check(WorldContextObject);
	const UWorld* World = WorldContextObject->GetWorld();
	check(World);

	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle, this, &UConsoleLearningDelay::OnTimerReady, DelayTime, false);
}

void UConsoleLearningDelay::OnTimerReady()
{
	OnDelayFinished.Broadcast();
}
