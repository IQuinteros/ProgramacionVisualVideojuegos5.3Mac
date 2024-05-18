// Docente Ignacio Quinteros

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/Object.h"
#include "ConsoleLearningDelay.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDelayFinished);

/**
 * Async action to simulate a set timer
 */
UCLASS()
class PROYECTOCLASE_API UConsoleLearningDelay : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnDelayFinished OnDelayFinished;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"))
	static UConsoleLearningDelay* LearningDelay(const UObject* WorldContextObject, float DelayTime);

	virtual void Activate() override;

	UPROPERTY()
	float DelayTime = -1.0f;

protected:

	UFUNCTION()
	void OnTimerReady();

private:

	UPROPERTY()
	const UObject* WorldContextObject;
	
};
