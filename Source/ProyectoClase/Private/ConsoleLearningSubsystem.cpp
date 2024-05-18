// Docente Ignacio Quinteros


#include "ConsoleLearningSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UConsoleLearningSubsystem::PrintMessage(const UObject* WorldContextObject, FString Message)
{
	check(WorldContextObject);

	UConsoleLearningSubsystem* LearningSubsystem = WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UConsoleLearningSubsystem>();
	check(LearningSubsystem);

	LearningSubsystem->PendingMessages.Add(Message);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(LearningSubsystem, &UConsoleLearningSubsystem::OnNextTick, Message);
	WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
}

void UConsoleLearningSubsystem::ReceivePrompt(FString Prompt)
{
	UE_LOG(LogTemp, Warning, TEXT("UConsoleLearningSubsystem::ReceivePrompt: Received prompt: %s"), *Prompt);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	OnPromptReceived.Broadcast(Prompt);
}

bool UConsoleLearningSubsystem::IsPausedGame()
{
	return UGameplayStatics::IsGamePaused(GetWorld());
}

void UConsoleLearningSubsystem::Internal_WaitPrompt() const
{
	UE_LOG(LogTemp, Warning, TEXT("UConsoleLearningSubsystem::Internal_WaitPrompt: Waiting for prompt..."));
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	OnPromptRequested.Broadcast();
}

void UConsoleLearningSubsystem::OnNextTick(FString Message)
{
	if(PendingMessages.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UConsoleLearningSubsystem::OnNextTick: No messages to print"));
		return;
	}
	
	const FString FirstMessage = PendingMessages[0];
	PendingMessages.RemoveAt(0);

	UE_LOG(LogTemp, Warning, TEXT("UConsoleLearningSubsystem::OnNextTick: Printing message: %s"), *FirstMessage);
	OnMessagePrinted.Broadcast(FirstMessage);
}
