#pragma once

namespace DebugHelper
{
	FORCEINLINE void Print(const FString& Msg, const int32 Key = 0, const FColor& Color = FColor::White)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(Key, 2.f, Color, Msg);
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
	}
}