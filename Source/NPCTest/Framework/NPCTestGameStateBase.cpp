// Copyright 2024 DME Games

#include "NPCTestGameStateBase.h"
#include "Kismet/KismetMathLibrary.h"

ANPCTestGameStateBase::ANPCTestGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Seconds = 0;
	Minutes = 30;
	Hours = 6;
	
	Day = 30;
	Month = 11;
	Year = 2;

	TimeUnit = 2.f;
	Clockwork = 0.f;
	DayTick = 0;	
}

void ANPCTestGameStateBase::AddNPCCharacter(ANPCCharacter* CharacterIn)
{
	if (!NPCsInWorldWithJobs.Contains(CharacterIn))
	{
		NPCsInWorldWithJobs.Add(CharacterIn, false);
	}
}

void ANPCTestGameStateBase::RemoveNPCCharacter(ANPCCharacter* CharacterIn)
{
	if (NPCsInWorldWithJobs.Contains(CharacterIn))
	{
		NPCsInWorldWithJobs.Remove(CharacterIn);
	}
}

void ANPCTestGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetDayTickAndClockwork(DeltaSeconds);
	SetClock();
	SetDate();

	GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Red, *FString::FromInt(NPCsInWorldWithJobs.Num()));
}

void ANPCTestGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	GameTime.Add(Seconds);
	GameTime.Add(Minutes);
	GameTime.Add(Hours);

	GameDate.Add(Day);
	GameDate.Add(Month);
	GameDate.Add(Year);

	Clockwork = Hours + (Minutes / 60.f);
}

void ANPCTestGameStateBase::SetDayTickAndClockwork(float DeltaTime)
{
	const float TimeUnitThisFrame = DeltaTime / TimeUnit;
	const float ClockworkThisFrame = TimeUnitThisFrame + Clockwork;
	DayTick = UKismetMathLibrary::FMod(ClockworkThisFrame, 24, Clockwork);
}

void ANPCTestGameStateBase::SetClock()
{
	// Get the current Minutes to see if this has changed
	const int32 OldMinutes = Minutes;

	// There are 3600 seconds in an hour 
	const float ClockworkPerHour = Clockwork * 3600;
	float SecondsAsFloat;
	// 60 Seconds in a Minutes
	const int32 RemainingSeconds = UKismetMathLibrary::FMod(ClockworkPerHour, 60, SecondsAsFloat);
	Seconds = FMath::Floor(SecondsAsFloat);
	float MinutesAsFloat;
	// 60 Minutes in an hour
	const int32 RemainingMinutes = UKismetMathLibrary::FMod(RemainingSeconds, 60, MinutesAsFloat);
	Minutes = FMath::Floor(MinutesAsFloat);
	float HoursAsFloat;
	// 24 Hours in a day
	int32 UnneededInt = UKismetMathLibrary::FMod(RemainingMinutes, 24, HoursAsFloat);
	Hours = FMath::Floor(HoursAsFloat);

	if ((Minutes != OldMinutes) && (Minutes == 0 || Minutes == 30))
	{
		const ETime ReturnedTime = BroadcastTimeChange();
		if (ReturnedTime != ETime::ET_FAIL)
		{
			OnMinutesUpdated.Broadcast(ReturnedTime);
		}
	}
	
	if (GameTime.Num() > 0)
	{
		GameTime[0] = Seconds;
		GameTime[1] = Minutes;
		GameTime[2] = Hours;
	}
	else
	{
		GameTime.Add(Seconds);
		GameTime.Add(Minutes);
		GameTime.Add(Hours);
	}

	const FString TimeToDisplay = FString::FromInt(Hours) + ":" + FString::FromInt(Minutes) + ":" + FString::FromInt(Seconds);
	//GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Green, *TimeToDisplay);
}

void ANPCTestGameStateBase::SetDate()
{
	Day += DayTick;
	// Check whether the day is greater than the available days in this month
	if (Day > UKismetMathLibrary::DaysInMonth(Year, Month))
	{
		Day = 1;
		if (Month < 12)
		{
			Month += 1;
		}
		else
		{
			Month = 1;
			Year += 1;
		}
	}

	GameDate[0] = Day;
	GameDate[1] = Month;
	GameDate[2] = Year;
	
	const FString DateToDisplay = FString::FromInt(Day) + "/" + FString::FromInt(Month) + "/" + FString::FromInt(Year);
	//GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Red, *DateToDisplay);
}

ETime ANPCTestGameStateBase::BroadcastTimeChange()
{
	//UE_LOG(LogTemp, Warning, TEXT("Time is now %i:%i"), Hours, Minutes);
	
	switch (Minutes)
	{
	case 0:
		{
			if (Hours == 0) { return ETime::ET_0000; }
			if (Hours == 1) { return ETime::ET_0100; }
			if (Hours == 2) { return ETime::ET_0200; }
			if (Hours == 3) { return ETime::ET_0300; }
			if (Hours == 4) { return ETime::ET_0400; }
			if (Hours == 5) { return ETime::ET_0500; }
			if (Hours == 6) { return ETime::ET_0600; }
			if (Hours == 7) { return ETime::ET_0700; }
			if (Hours == 8) { return ETime::ET_0800; }
			if (Hours == 9) { return ETime::ET_0900; }
			if (Hours == 10) { return ETime::ET_1000; }
			if (Hours == 11) { return ETime::ET_1100; }
			if (Hours == 12) { return ETime::ET_1200; }
			if (Hours == 13) { return ETime::ET_1300; }
			if (Hours == 14) { return ETime::ET_1400; }
			if (Hours == 15) { return ETime::ET_1500; }
			if (Hours == 16) { return ETime::ET_1600; }
			if (Hours == 17) { return ETime::ET_1700; }
			if (Hours == 18) { return ETime::ET_1800; }
			if (Hours == 19) { return ETime::ET_1900; }
			if (Hours == 20) { return ETime::ET_2000; }
			if (Hours == 21) { return ETime::ET_2100; }
			if (Hours == 22) { return ETime::ET_2200; }
			if (Hours == 23) { return ETime::ET_2300; }
			
			return ETime::ET_FAIL;
		}
	case 30:
		{
			if (Hours == 0) { return ETime::ET_0030; }
			if (Hours == 1) { return ETime::ET_0130; }
			if (Hours == 2) { return ETime::ET_0230; }
			if (Hours == 3) { return ETime::ET_0330; }
			if (Hours == 4) { return ETime::ET_0430; }
			if (Hours == 5) { return ETime::ET_0530; }
			if (Hours == 6) { return ETime::ET_0630; }
			if (Hours == 7) { return ETime::ET_0730; }
			if (Hours == 8) { return ETime::ET_0830; }
			if (Hours == 9) { return ETime::ET_0930; }
			if (Hours == 10) { return ETime::ET_1300; }
			if (Hours == 11) { return ETime::ET_1130; }
			if (Hours == 12) { return ETime::ET_1230; }
			if (Hours == 13) { return ETime::ET_1330; }
			if (Hours == 14) { return ETime::ET_1430; }
			if (Hours == 15) { return ETime::ET_1530; }
			if (Hours == 16) { return ETime::ET_1630; }
			if (Hours == 17) { return ETime::ET_1730; }
			if (Hours == 18) { return ETime::ET_1830; }
			if (Hours == 19) { return ETime::ET_1930; }
			if (Hours == 20) { return ETime::ET_2300; }
			if (Hours == 21) { return ETime::ET_2130; }
			if (Hours == 22) { return ETime::ET_2230; }
			if (Hours == 23) { return ETime::ET_2330; }
			return ETime::ET_FAIL;
		}
	default:
			return ETime::ET_FAIL;
	}
}
