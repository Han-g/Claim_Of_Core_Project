#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGMManager.generated.h"

class USoundBase;
class UAudioComponent;

UCLASS()
class CLAIM_OF_CORE_API ABGMManager : public AActor
{
	GENERATED_BODY()

public:
	ABGMManager();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> BGM;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	float Volume = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	bool bLoop = true;

private:
	UPROPERTY()
	TObjectPtr<UAudioComponent> BGMComponent;
};
