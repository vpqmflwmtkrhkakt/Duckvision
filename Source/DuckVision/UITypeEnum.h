#pragma once

#include "CoreMinimal.h"
#include "UITypeEnum.generated.h"

/*
* Toggle할때 필요한 UIType
*/
UENUM(BlueprintType)
enum class UITypeEnum : uint8
{
    Pause           UMETA(DisplayName="Pause"),
    Map             UMETA(DisplayName="Map"),
    Equipment       UMETA(DisplayName="Equipment"),
    SearchResult    UMETA(DisplayName="SearchResult")
};
