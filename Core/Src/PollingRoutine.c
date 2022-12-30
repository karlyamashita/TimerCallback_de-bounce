/*
 * PollingRoutine.c
 *
 *  Created on: Dec 24, 2022
 *      Author: codek
 *
 *
 *      This project is using an STM32F4DISCOVERY
 *
 *
 *
 *
 *
 *
 */

#include "main.h"
#include "PollingRoutine.h"


extern TimerCallbackStruct timerCallback;




/*
 * Description: called once before main while loop
 */
void PollingInit(void)
{
//****** register callbacks **************
	TimerCallbackRegisterOnly(&timerCallback, BlinkGreenLED);
	TimerCallbackRegisterOnly(&timerCallback, BlinkAmberLED);
	TimerCallbackRegisterOnly(&timerCallback, BlinkBlueLED);
	// Push Button related
#ifdef USE_BUTTON_EXAMPLE
	TimerCallbackRegisterOnly(&timerCallback, DebouncePB);
	#ifdef NORMAL_DEBOUNCE_BUTTON_COUNTER
	TimerCallbackRegisterOnly(&timerCallback, ButtonCounter);
	TimerCallbackRegisterOnly(&timerCallback, ButtonCountDone);
	#endif // NORMAL_DEBOUNCE_BUTTON_COUNTER
#endif


//************* On POR, start off with blinking two LEDs at different rates *****************
	// This will toggle the green led at 500ms rate, so the LED On state will be at a 1 second interval.
	TimerCallbackTimerStart(&timerCallback, BlinkGreenLED, 500, TIMER_REPEAT);
	// This will toggle the amber led at 100ms rate, so fast blinking
	TimerCallbackTimerStart(&timerCallback, BlinkAmberLED, 100, TIMER_REPEAT);

	// in Example.c
	Example();

}

/*
 * Description: main while loop
 */
void PollingRoutine(void)
{
	// This needs to be called constantly in order for any register callback functions to do a task at a given time.
	TimerCallbackCheck(&timerCallback);

	// other tasks
}

