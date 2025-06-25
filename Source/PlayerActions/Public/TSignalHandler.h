// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformMisc.h"

class PLAYERACTIONS_API ISignalHandlerBase
{
public:
    virtual ~ISignalHandlerBase() = default;
};

template<typename TSignal>
class TSignalHandler: public ISignalHandlerBase
{
public:
    TArray<TFunction<void(const TSignal&)>> Handlers;

    void AddHandler(TFunction<void(const TSignal&)> Handler)
    {
        Handlers.Add(Handler);
    }

    void Dispatch(const TSignal& Signal)
    {
        for (auto& Handler : Handlers)
        {
            Handler(Signal);
        }
    }
};
