#pragma once
#include "CoreMinimal.h"
#include "TSignalHandler.h"


class PLAYERACTIONS_API EventBus
{
private:
	EventBus(){}
	EventBus(const EventBus&) = delete;
	EventBus& operator=(const EventBus&) = delete;

	

public:
	static EventBus& GetInst();
	
	template<typename TSignal>
	void RegisterHandler(TFunction<void(const TSignal&)> Handler)
	{
		FName SignalName = TSignal::GetSignalName();

		if (!Handlers.Contains(SignalName))
		{
			Handlers.Add(SignalName, MakeShared<TSignalHandler<TSignal>>());
		}

		TSharedPtr<TSignalHandler<TSignal>> TypedHandler = StaticCastSharedPtr<TSignalHandler<TSignal>>(Handlers[SignalName]);
		TypedHandler->AddHandler(Handler);
	}

	template<typename TSignal>
	void Dispatch(const TSignal& Signal)
	{
		FName SignalName = TSignal::GetSignalName();

		if (Handlers.Contains(SignalName))
		{
			TSharedPtr<TSignalHandler<TSignal>> TypedHandler = StaticCastSharedPtr<TSignalHandler<TSignal>>(Handlers[SignalName]);
			TypedHandler->Dispatch(Signal);
		}
	}

private:
	TMap<FName, TSharedPtr<ISignalHandlerBase>> Handlers;
};
