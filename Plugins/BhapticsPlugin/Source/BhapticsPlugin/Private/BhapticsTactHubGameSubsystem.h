/*
* Copyright (c) 2024 bHaptics Inc.
 *
 * This project incorporates components from the bHaptics SDK, which is utilized under the terms of the bHaptics SDK Agreement.
 * For the complete terms and conditions governing the use of the bHaptics SDK, please refer to https://bhaptics.gitbook.io/license-sdk/.
 *
 * Use of the bHaptics SDK is strictly in accordance with the aforementioned agreement. Unauthorized use, sharing, modification,
 * or distribution of the SDK outside the terms of this agreement is prohibited.
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "BhapticsStructs.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BhapticsTactHubGameSubsystem.generated.h"

UCLASS()
class UBhapticsTactHubGameSubsystem  : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	static void InitializeSDK(const FString& AppId, const FString& ApiKey);
	static int PlayHaptic(const FString& EventName, const int RequestId);
	static int PlayHapticWithOptions(
		const FString& EventName, const int RequestId,
		float IntensityRatio, float DurationRatio,
		float OffsetAngleX, float OffsetY
		);
	static int PlayHapticWithStartTime(const FString& EventName, int RequestId, int StartMillis, float IntensityRatio,
		float DurationRatio, float OffsetAngleX, float OffsetY);

	static int PlayLoopHapticWithOptions(
		const FString& EventName, const int RequestId, const float IntensityRatio, const float DurationRatio,
		const float OffsetAngleX, const float OffsetY, const int Interval, const int MaxCount);

	static int PlayMotors(
		const int RequestId, const int Pos, const int DurationMillis,
		const TArray<int>& Motors);
	
	static int PlayPath(
		const int Pos, const int RequestId, const int DurationMillis,
		const TArray<float>& X,
		const TArray<float>& Y,
		const TArray<int>& Motors);

	static int PlayWaveform(
		const int RequestId, const int Pos,
		const TArray<EBhapticsGlovePlayTime>& PlayTimeValues, const TArray<EBhapticsGloveShapeValue>& ShapeValues,
		const TArray<int>& Motors);
	
	static void StopByRequestId(int RequestId);
	static void StopByEventName(const FString& EventName);
	static void StopAll();

	static void Ping(FBhapticsDevice Device);
	static void PingAll();

	static void PauseByEventId(FString EventId);
	static void ResumeByEventId(FString EventId);

	static void SwapPosition(FBhapticsDevice Device);

private:
	FTimerHandle TimerHandle;
	void SetTimer();
	static void OnCheck();
	static void SendPingToServer();
	static int HubAuthMessageVersion;

	static TArray<int> ConvertEnumArrayToIntArray(const TArray<EBhapticsGlovePlayTime>& EnumArray);
	static TArray<int> ConvertEnumArrayToIntArray(const TArray<EBhapticsGloveShapeValue>& EnumArray);

};
