#pragma once

#include "CoreMinimal.h"
#include "UITypeEnum.generated.h"

/*
* Toggle할때 필요한 UIType
*/
UENUM(BlueprintType)
enum class UITypeEnum : uint8
{
    Inventory UMETA(DisplayName="Inventory"),
    Pause     UMETA(DisplayName="Pause"),
    Shop      UMETA(DisplayName="Shop"),
    Map       UMETA(DisplayName="Map"),
    Equipment UMETA(DisplayName="Equipment")
};
