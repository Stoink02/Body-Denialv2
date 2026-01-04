//Copyright bHaptics Inc. All Rights Reserved 2022~

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BhapticsSettings.h"

#include "BhapticsSDK2.generated.h"

UCLASS()
class BHAPTICSPLUGIN_API UBhapticsSDK2 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Initialize the haptic environment. This function should be called before using the haptic-related functions.
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Initialize bHaptics",
			Keywords = "bHaptics",
			tooltip = "Initialize the haptic environment. This function should be called before using the haptic-related functions."),
		Category = "bHaptics"
	)
	static void Initialize();

	/**
	* Play haptic event, It has the lowest overhead of any haptic event-calling function.
	*
	* @param	eventId			- Name of haptic event which you want to play.
	*							  eventId refers to the name of an event as defined on developer.bhaptics.com.
	*
	* @return RequestId. You can use the requestId to stop the haptic. It returns -1 if the return fails.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Play Haptic",
			Keywords = "bHaptics",
			tooltip = "Play the haptic event. It is the most basic way to call a haptic event. It has the lowest overhead of any haptic event-calling function."),
		Category = "bHaptics"
	)
	static int PlayHaptic(FString eventId);

	/**
	* Play haptic event, You can use this function to control the strength, duration, and direction of the haptic.
	*
	* @param	eventId			- Name of haptic event which you want to play.
	*							  eventId refers to the name of an event as defined on developer.bhaptics.com.
	* @param	intensity		- The haptic intensity is multiplied by this value.
	* @param	duration		- The haptic duration is multiplied by this value.
	* @param	angleX			- Rotate haptic counterclockwise around the global Vector3.up. Valid range is: [0.0f - 360.0f]
	* @param	offsetY			- Move haptic up or down. Valid range is: [-0.5f - 0.5f]
	*
	* @return RequestId. You can use the requestId to stop the haptic. It returns -1 if the return fails.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Play Haptic With Option",
			Keywords = "bHaptics",
			tooltip = "Play haptic event, with adjusting the strength, duration, and direction of the haptic."),
		Category = "bHaptics"
	)
	static int PlayHapticWithOption(FString eventId, float intensity = 1.0f, float duration = 1.0f, float angleX = 0.0f, float offsetY = 0.0f);

	/**
	* Play haptic event, You can use this function to control the strength, duration, and direction of the haptic.
	*
	* @param	eventId			- Name of haptic event which you want to play.
	*							  eventId refers to the name of an event as defined on developer.bhaptics.com.
	* @param	startMillis		- [windows/android Only] The delay in milliseconds before the haptic event starts playing. The haptic will begin after this time has elapsed.
	* @param	intensity		- The haptic intensity is multiplied by this value.
	* @param	duration		- The haptic duration is multiplied by this value.
	* @param	angleX			- Rotate haptic counterclockwise around the global Vector3.up. Valid range is: [0.0f - 360.0f]
	* @param	offsetY			- Move haptic up or down. Valid range is: [-0.5f - 0.5f]
	*
	* @return RequestId. You can use the requestId to stop the haptic. It returns -1 if the return fails.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Play Haptic With StartTime",
			Keywords = "bHaptics",
			tooltip = "Play haptic event, with adjusting the StartTime, strength, duration, and direction of the haptic."),
		Category = "bHaptics"
	)
	static int PlayWithStartTime(FString eventId, int startMillis = 0, float intensity = 1.0f, float duration = 1.0f, float angleX = 0.0f, float offsetY = 0.0f);

	/**
	* If you don't want to create an event, call this Function
	* 
	* @param	position		- Type of haptic device.
	* @param	motorValues		- Assign the length of the array by the number of motors for device. Values in the array means motors' intensity. Valid range for each value in the array is: [1 - 100]
	* @param	seconds			- The duration of haptic, measured in second. Greater than or equal to 0.1f is recommended.
	*
	* @return RequestId. You can use the requestId to stop the haptic. It returns -1 if the return fails.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Play Dot",
			Keywords = "bHaptics",
			tooltip = "Play haptic feedback on the specific haptic actuator."),
		Category = "bHaptics"
	)
	static int PlayDot(int position, TArray<int> motorValues, float seconds = 0.5f);

	/**
	* Play haptic around specific coordinates. See C++ API Reference for more information in docs.
	* 
	* @param	position		- Type of haptic device.
	* @param	x				- Assign X coordinate. Valid range for each value in the array is: [0.0f - 1.0f]
	* @param	y				- Assign y coordinate. Assign Y coordinate. Valid range for each value in the array is: [0.0f - 1.0f]
	* @param	motorValues		- Assign the length of the array by the number of motors for device. Values in the array means motors' intensity. Valid range for each value in the array is: [1 - 100]
	* @param	seconds			- The duration of haptic, measured in second. Greater than or equal to 0.1f is recommended.
	*
	* @return RequestId. You can use the requestId to stop the haptic. It returns -1 if the return fails.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Play Path",
			Keywords = "bHaptics",
			tooltip = "Play haptic around specific coordinates."),
		Category = "bHaptics"
	)
	static int PlayPath(int position, TArray<float> x, TArray<float> y, TArray<int> motorValues, float seconds = 0.5);

	/**
	* [TactGlove-Only] Play haptics in TactGlove. Unlike using "Play Dot", you can finely adjust haptic duration and vibration intensity changes. This allows for even finer expression of haptic feedback.
	* Each array must have six elements, and at least one element is required to work.
	* 
	* @param    position		 - Type of haptic device. GloveL = 8, GloveR = 9
	* @param	motorIntensities - An array consisting of six elements, each representing the intensity of a motor. The array must have a length of six, as there are six motors in one TactGlove. 
	*								  Valid range for each value in the array is: [1 - 100]
	* @param	playTimeValues	 - An array consisting of six elements, each representing a time interval for actuation, with time defined using EBhapticsGlovePlayTime enums.
	* @param	shapeValues		 - An array consisting of six elements, each representing the forms of haptic intensity changes over time, specified by the EBhapticsGloveShapeValue enums.
	*
	* @return RequestId. You can use the requestId to stop the haptic. It returns -1 if the return fails.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Play Waveform",
			Keywords = "bHaptics",
			tooltip = "[Glove-only func]If you don't want to create an event, call this Function"),
		Category = "bHaptics"
	)
	static int PlayWaveform(int position, TArray<int> motorIntensities, TArray<EBhapticsGlovePlayTime> playTimeValues, TArray<EBhapticsGloveShapeValue> shapeValues);

	/**
	* Play the haptic repeatedly. Additionally, like the function PlayHapticWithOption, you can adjust the strength, duration, and direction of the haptic.
	* 
	* @param	eventId			- Name of haptic event which you want to play.
	*							  eventId refers to the name of an event as defined on developer.bhaptics.com.
	* @param	intensity		- The haptic intensity is multiplied by this value.
	* @param	duration		- The haptic duration is multiplied by this value.
	* @param	angleX			- Rotate haptic counterclockwise around the global Vector3.up. Valid range is: [0.0f - 360.0f]
	* @param	offsetY			- Move haptic up or down. Valid range is: [-0.5f - 0.5f]
	* @param	interval		- The time interval between loops, measured in milliseconds.
	* @param	maxCount		- The number of loops.
	*
	* @return RequestId. You can use the requestId to stop the haptic. It returns -1 if the return fails.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Play Loop",
			Keywords = "bHaptics",
			tooltip = "Play the haptic repeatedly. Additionally, like the function PlayHapticWithOption, you can adjust the strength, duration, and direction of the haptic."),
		Category = "bHaptics"
	)
	static int PlayLoop(FString eventId, float intensity = 1.0f, float duration = 1.0f, float angleX = 0.0f, float offsetY = 0.0f, int interval = 200, int maxCount = 999999);


	/**
	* Stop the haptic event by eventId. Returns whether the stop was successful.
	*
	* @param	eventId			- Name of haptic event which you want to stop.
	*							  eventId refers to the name of an event as defined on developer.bhaptics.com.
	*
	* @return Returns Whether the stop was successful.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Stop Haptic By EventId",
			Keywords = "bHaptics",
			tooltip = "Stop the haptic event by EventId"),
		Category = "bHaptics"
	)
	static bool StopHapticByEventId(FString eventId);

	/**
	* Stop the Haptic Event by using the RequestId from the return of the function that executes the haptic.
	*
	* @param	requestId		- RequestId of playing haptic event which you want to stop.
	*
	* @return Returns Whether the stop was successful.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Stop Haptic By RequestId",
			Keywords = "bHaptics",
			tooltip = "Stop the Haptic Event by using the RequestId from the return of the function that executes the haptic."),
		Category = "bHaptics"
	)
	static bool StopHapticByRequestId(int requestId);


	/**
	* Stops all haptic currently playing.
	* 
	* @return Returns Whether the stop was successful.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Stop Haptic",
			Keywords = "bHaptics",
			tooltip = "Stops all haptic currently playing."),
		Category = "bHaptics"
	)
	static bool StopHaptic();

	/**
	* Send simple haptic feedback to certain device.
	*
	* @param	device			- Device you want to send ping.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Ping",
			Keywords = "bHaptics",
			tooltip = "Send simple haptic feedback to certain device."),
		Category = "bHaptics"
	)
	static void Ping(FBhapticsDevice device);

	//Send simple haptic feedback to all connected devices.
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Ping All",
			Keywords = "bHaptics",
			tooltip = "Send simple haptic feedback to all connected devices."),
		Category = "bHaptics"
	)
	static void PingAll();

	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Swap Position",
			Keywords = "bHaptics"),
		Category = "bHaptics"
	)
	static void SwapPosition(FBhapticsDevice device);

	/**
	* Check if the haptic is playing.
	* @return Whether the event is playing.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Is Playing",
			Keywords = "bHaptics",
			tooltip = "Check if the haptic is playing."),
		Category = "bHaptics"
	)
	static bool IsPlaying();

	/**
	* Check if the haptic event for this RequestId is playing.
	*
	* @param	requestId		- RequestId of haptic event to check if it is currently playing.
	*
	* @return Whether the event is playing.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Is Playing By RequestId",
			Keywords = "bHaptics",
			tooltip = "Check if the haptic event for this RequestId is playing."),
		Category = "bHaptics"
	)
	static bool IsPlayingByRequestId(int requestId);

	/**
	* Check if the haptic event for this EventId is playing.
	*
	* @param	eventId			- Name of haptic event to check if it is currently playing.
	*							  eventId refers to the name of an event as defined on developer.bhaptics.com.
	*
	* @return Whether the event is playing.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Is Playing By EventId",
			Keywords = "bHaptics",
			tooltip = "Check if the haptic event for this EventId is playing."),
		Category = "bHaptics"
	)
	static bool IsPlayingByEventId(FString eventId);

	//Destroy the haptic environment. This function must be called when game ends, and called ONLY ONCE.
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Destroy bHaptics",
			Keywords = "bHaptics",
			tooltip = "Destroy the haptic environment. This function must be called when game ends, and called ONLY ONCE."),
		Category = "bHaptics"
	)
	static void Destroy();
	
	/**
	* Get an array of connected haptic devices info.
	* @return List of devices.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Get bHaptics devices",
			Keywords = "bHaptics",
			tooltip = "Get an array of connected haptic devices info."),
		Category = "bHaptics"
	)
	static TArray<FBhapticsDevice> GetBhapticsDevices();

	/**
	* Check if the haptic environment is initialized, and ready to use haptic-related functions.
	* @return Whether the bHaptics environment is available.
	*/
	UFUNCTION(
		BlueprintCallable,
		meta = (DisplayName = "Is bHaptics Available",
			Keywords = "bHaptics",
			tooltip = "Whether the bHaptics environment is available."),
		Category = "bHaptics"
	)
	static bool IsBhapticsAvailable();

	/**
	* Helper function to compute the offset values (angle and height) of a given collision contact point from the player. These offset values can be used in PlayHapticWithOption and PlayLoop which can adjust the haptic position.
	* This function assumes that the forward direction aligns with the front of the vest, and the player's position is considered as the origin. See C++ API Reference for more information in docs.
	*
	* @param	ContactLocation	- Contact point in global coordinates.
	* @param	PlayerComponent	- Reference to the primitive component attached to the player.
	* @param	HalfHeight			- The half value of the player's actual height, measured in centimeter.
	*
	* @return Offset values.
	*/
	UFUNCTION(BlueprintPure,
		meta = (DisplayName = "Project To Vest With Player Collision Object",
			Keywords = "bHaptics",
			tooltip = "Helper function to compute the offset values (angle and height) of a given collision contact point from the player."),
		Category = "bHaptics")
	static FBhapticsRotationOption ProjectToVest(FVector ContactLocation, UPrimitiveComponent* PlayerComponent, float HalfHeight = 0);

	/**
	* Helper function to compute offset values from a contact location and player transform information.
	* It's similar to "Project To Vest", but it only calculates the angle offset(Offset Angle X). The height(Offset Y) will always be 0.
	*
	* @param	ContactLocation	- Contact point in global coordinates.
	* @param	PlayerLocation	- Location of the player.
	* @param	PlayerRotation	- Rotation of the player.
	*
	* @return Offset values.
	*/
	UFUNCTION(BlueprintPure,
		meta = (DisplayName = "Project To Vest With Player Location/Position",
			Keywords = "bHaptics",
			tooltip = "Helper function to compute offset values from a contact location and player transform information."),
		Category = "bHaptics")
	static FBhapticsRotationOption ProjectToVestLocation(FVector ContactLocation, FVector PlayerLocation, FRotator PlayerRotation);

	/**
	* Helper function to compute offset values from collision. Performs the same function as "Project To Vest", but allows the Forward and Up vectors to be changed.
	*
	* @param	ContactLocation	- Contact point in global coordinates.
	* @param	PlayerComponent	- Reference to the primitive component attached to the player.
	* @param	HalfHeight		- The half value of the player's actual height, measured in centimeter.
	* @param	UpVector		- The reference upward direction vector for offset calculation.
	* @param	ForwardVector	- The reference forward direction vector for offset calculation.
	*
	* @return Offset values.
	*/
	UFUNCTION(BlueprintPure,
		meta = (DisplayName = "Custom Project To Vest",
			Keywords = "bHaptics",
			AdvancedDisplay = "3",
			tooltip = "Helper function to compute offset values from collision. Performs the same function as Project To Vest"),
		Category = "bHaptics")
	static FBhapticsRotationOption CustomProjectToVest(FVector ContactLocation, UPrimitiveComponent* PlayerComponent, float HalfHeight = 0, FVector UpVector = FVector::ZeroVector, FVector ForwardVector = FVector::ZeroVector);

	static UBhapticsSettings* TryLoadBhapticsConfig();

private:
	static bool TryInitializeAndCheck();
	static bool AutoLaunchPlayer;
	static int GetRequestId();
};

