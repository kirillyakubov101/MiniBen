#pragma once
#include "CoreMinimal.h"
#include "../Public/Signals/Signals.h"


class PLAYERACTIONS_API EventBus
{
private:
	EventBus(){}
	EventBus(const EventBus&) = delete;
	EventBus& operator=(const EventBus&) = delete;

	using FSignalCallback = TFunction<void(const FBaseSignal&)>;

public:
	static EventBus& GetInst();

	template<typename TSignal>
	void Subscribe(TFunction<void(const TSignal&)> Callback)
	{
		FString SignalName = TSignal::StaticStruct()->GetName();

		FSignalCallback Wrapper = [Callback](const FBaseSignal& BaseSignal)
			{
				const TSignal& Typed = static_cast<const TSignal&>(BaseSignal);
				Callback(Typed);
			};

		SignalBus.FindOrAdd(SignalName).Add(Wrapper);
	}

	template<typename TSignal>
	void Invoke(const TSignal& Signal)
	{
		static_assert(std::is_base_of<FBaseSignal, TSignal>::value, "Signal must derive from FBaseSignal");

		FString SignalName = TSignal::StaticStruct()->GetName();

		if (TArray<FSignalCallback>* Callbacks = SignalBus.Find(SignalName))
		{
			for (auto& Callback : *Callbacks)
			{
				Callback(Signal); // Pass as FBaseSignal reference
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No subscribers for signal type: %s"), *SignalName);
		}
	}
	

private:
	TMap<FString, TArray<FSignalCallback>> SignalBus;
};
