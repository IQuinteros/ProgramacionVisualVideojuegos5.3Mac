// Docente Ignacio Quinteros

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/Object.h"
#include "WaitPrompt.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPromptSignature, FString, Prompt);

/**
 * Async action that waits for a prompt to be received by the user
 */
UCLASS(DisplayName="Prompt Message")
class PROYECTOCLASE_API UWaitPrompt : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FPromptSignature OnPromptReceived;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"))
	static UWaitPrompt* PromptMessage(const UObject* WorldContextObject);

	virtual void Activate() override;

protected:

	UFUNCTION()
	void OnPromptReady(FString Prompt);

	UFUNCTION()
	void OnNextTick();

private:

	UPROPERTY()
	const UObject* WorldContextObject;
	
};
