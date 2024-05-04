// Docente Ignacio Quinteros

#pragma once

#include "CoreMinimal.h"
#include "WaitPrompt.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConsoleLearningSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPrintMessageSignature, FString, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRequestedPromptSignature);


/**
 * 
 */
UCLASS()
class PROYECTOCLASE_API UConsoleLearningSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FPrintMessageSignature OnMessagePrinted;

	UPROPERTY(BlueprintAssignable)
	FPromptSignature OnPromptReceived;

	UPROPERTY(BlueprintAssignable)
	FRequestedPromptSignature OnPromptRequested;

public:

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static void PrintMessage(const UObject* WorldContextObject, FString Message);

	UFUNCTION(BlueprintCallable)
	void ReceivePrompt(FString Prompt);

public:

	void Internal_WaitPrompt() const;

protected:

	UFUNCTION()
	void OnNextTick(FString Message);

	UPROPERTY()
	TArray<FString> PendingMessages;
	
};
