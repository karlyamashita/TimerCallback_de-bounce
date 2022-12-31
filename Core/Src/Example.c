/*
 * Example.c
 *
 *  Created on: Dec 26, 2022
 *      Author: codek
 */

#include "main.h"
#include "Example.h"


extern TimerCallbackStruct timerCallback;



void Example(void)
{
#ifdef EXAMPLE_1 //************ set up a repetition timer ****************
	// This will toggle the blue led 10 times. So 5 On states and 5 Off states with 500ms between each call to BlinkBlueLED.
	TimerCallbackRepetitionStart(&timerCallback, BlinkBlueLED, 500, 10);
#endif

#ifdef EXAMPLE_2 //*************** using a Structure to set up a timer **************
	TimerCallbackStruct timerCallbackInit = {0}; // use for registering a callback passing a structured argument

	timerCallbackInit.callback = BlinkBlueLED;
	timerCallbackInit.timerValue = 500;
	timerCallbackInit.timerRepeat = true;
	timerCallbackInit.timerEnabled = true;

	timerCallbackInit.timerRepetitionValue = 6;
	timerCallbackInit.timerRepetitionEnable = true;

	timerCallbackInit.callback2 = SetRedLED;
	timerCallbackInit.timerCallback2Enabled = true;
	TimerCallbackRegisterStruct(&timerCallback, &timerCallbackInit);
#endif

#ifdef EXAMPLE_3
	// this will toggle the blue led at a rate of 333ms between each callback for 5 seconds
	TimerCallbackTimeoutStart(&timerCallback, BlinkBlueLED, 333, 3100);
#endif


}
