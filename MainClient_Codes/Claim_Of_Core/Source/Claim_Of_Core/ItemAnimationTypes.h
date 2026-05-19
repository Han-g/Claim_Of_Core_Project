#pragma once

#include "CoreMinimal.h"
#include "ItemAnimationTypes.generated.h"

UENUM(BlueprintType)
enum class EItemAnimPoseType : uint8
{
	None UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"),
	Spear UMETA(DisplayName = "Spear"),
	Hammer UMETA(DisplayName = "Hammer")
};
