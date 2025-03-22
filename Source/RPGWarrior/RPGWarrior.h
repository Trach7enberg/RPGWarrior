// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DEFINE_LOG_CATEGORY_STATIC(RPGWarriorDebugLog, All, All);

namespace RPGWarriorDebug
{
	static void Print(
		const FString&            Msg,
		const FColor&             Color           = FColor::MakeRandomColor(),
		const int32               InKey           = -1,
		const float               InTimeToDisplay = 4.f,
		const ELogVerbosity::Type InLogLevel      = ELogVerbosity::Warning)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, InTimeToDisplay, Color, Msg);
			switch (InLogLevel)
			{
				case ELogVerbosity::Error:
					UE_LOG(RPGWarriorDebugLog, Error, TEXT("[%hs]: %s"),__FUNCTION__ , *Msg);
					break;
				case ELogVerbosity::Warning:
					UE_LOG(RPGWarriorDebugLog, Warning, TEXT("[%hs]: %s"), __FUNCTION__, *Msg);
					break;
				case ELogVerbosity::Log:
					UE_LOG(RPGWarriorDebugLog, Log, TEXT("[%hs]: %s"), __FUNCTION__, *Msg);
					break;
				default:
					break;
			}
		}
	}
}
