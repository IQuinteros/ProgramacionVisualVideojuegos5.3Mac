// Docente Ignacio Quinteros


#include "WaitPrompt.h"

#include "ConsoleLearningSubsystem.h"

UWaitPrompt* UWaitPrompt::PromptMessage(const UObject* WorldContextObject)
{
	UWaitPrompt* BlueprintNode = NewObject<UWaitPrompt>();
	BlueprintNode->WorldContextObject = WorldContextObject;
	return BlueprintNode;
}

void UWaitPrompt::Activate()
{
	Super::Activate();
	check(WorldContextObject);
	const UWorld* World = WorldContextObject->GetWorld();
	check(World);
	
	World->GetTimerManager().SetTimerForNextTick(this, &UWaitPrompt::OnNextTick);
}

void UWaitPrompt::OnPromptReady(FString Prompt)
{
	UE_LOG(LogTemp, Warning, TEXT("UWaitPrompt::OnPromptReady: Received prompt: %s"), *Prompt);
		
	OnPromptReceived.Broadcast(Prompt);
	
	check(WorldContextObject);
	const UWorld* World = WorldContextObject->GetWorld();
	check(World);
	
	UConsoleLearningSubsystem* LearningSubsystem = World->GetGameInstance()->GetSubsystem<UConsoleLearningSubsystem>();
	check(LearningSubsystem);

	LearningSubsystem->OnPromptReceived.RemoveDynamic(this, &UWaitPrompt::OnPromptReady);
}

void UWaitPrompt::OnNextTick()
{
	check(WorldContextObject);
	const UWorld* World = WorldContextObject->GetWorld();
	check(World);
	
	UConsoleLearningSubsystem* LearningSubsystem = World->GetGameInstance()->GetSubsystem<UConsoleLearningSubsystem>();
	check(LearningSubsystem);

	if(!LearningSubsystem->OnPromptReceived.IsAlreadyBound(this, &UWaitPrompt::OnPromptReady))
	{
		LearningSubsystem->OnPromptReceived.AddDynamic(this, &UWaitPrompt::OnPromptReady);
	}
	
	LearningSubsystem->Internal_WaitPrompt();
}
