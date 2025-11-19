#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h" // ← 철자 수정!

// Unreal reflection system용 UInterface 선언
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

// 실제 인터페이스 함수들을 선언하는 부분
class DUCKVISION_API IInteractableInterface
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* Caller) = 0;
};
