/*
 * ButtonCounter.c
 *
 *  Created on: Dec 26, 2022
 *      Author: codek
 */

#include "main.h"
#include "ButtonCounter.h"


// need to include TimerCallback.h with Rev 2.5. Newer revisions might be ok unless I update the structure and function names.
extern TimerCallbackStruct timerCallback;

#ifdef USE_BUTTON_EXAMPLE


uint32_t buttonCount = 0;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint32_t buttonState;

	if(GPIO_Pin == PushButtonPin) // test to be sure Push Button caused interrupt
	{
		buttonState = HAL_GPIO_ReadPin(B1_GPIO_Port, PushButtonPin); // we know what pin caused interrupt but now we need to get the state of the button
		if(buttonState == GPIO_PIN_SET)
		{

#ifdef NO_DEBOUNCE // Purposely set to 0ms to simulate no de-bouncing of button.
	TimerCallbackTimerStart(&timerCallback, DebouncePB, 0, TIMER_NO_REPEAT); // one shot
	#define USE_0_MS
#endif
#ifdef NORMAL_DEBOUNCE // Then set to 5ms
	TimerCallbackTimerStart(&timerCallback, DebouncePB, 20, TIMER_NO_REPEAT);// one shot
	#define USE_1000_MS
#endif
#ifdef NORMAL_DEBOUNCE_BUTTON_COUNTER // Then set to 5ms
	TimerCallbackTimerStart(&timerCallback, DebouncePB, 5, TIMER_NO_REPEAT);// one shot
	#define USE_BUTTON_COUNTER
#endif
		}
		else // buttonState == GPIO_PIN_RESET
		{
			// Button was release so disable these callbacks
			TimerCallbackDisable(&timerCallback, DebouncePB);
			TimerCallbackDisable(&timerCallback, BlinkBlueLED);
#ifdef USE_BUTTON_COUNTER
			TimerCallbackTimerStart(&timerCallback, ButtonCountDone, 700, TIMER_REPEAT);
#endif
			// Turn Off red led
			ClearRedLED();
		}
	}
}


void DebouncePB(void)
{
#ifdef USE_1000_MS
	// This is an alternative delay after the button is de-bounced. We are going to wait another 1 second before turning on the blue led
	TimerCallbackTimerStart(&timerCallback, BlinkBlueLED, 1000, TIMER_NO_REPEAT);// one shot
#endif
#ifdef USE_0_MS
	// no delay to demonstrate that with no de-bounce that the PB can trigger another event
	TimerCallbackTimerStart(&timerCallback, BlinkBlueLED, 0, TIMER_NO_REPEAT); // one shot
#endif
#ifdef USE_BUTTON_COUNTER
	TimerCallbackDisable(&timerCallback, ButtonCountDone);
	ButtonCounter();
#endif
	// button has been de-bounced so turn on red led
	SetRedLED();
}

#ifdef USE_BUTTON_COUNTER

void ButtonCounter(void)
{
	++buttonCount;
}

void ButtonCountDone(void)
{
	// disable callback so this function is not called again.
	TimerCallbackDisable(&timerCallback, ButtonCountDone);


	// Blink blue led the value of ButtonCount. For each blink it takes two calls, so we need to double the ButtonCount.
	TimerCallbackRepetitionStart(&timerCallback, BlinkBlueLED, 250, buttonCount * 2);
	// And instead of blinking led, you could pass ButtonCount value to a function to do some other task all together.
#ifdef CHANGE_BLINK_RATE
	if(buttonCount == 1)
	{
		TimerCallbackTimerStart(&timerCallback, BlinkAmberLED, 1000, TIMER_REPEAT);
	}
	else if(buttonCount == 2)
	{
		TimerCallbackTimerStart(&timerCallback, BlinkAmberLED, 500, TIMER_REPEAT);
	}
	else if(buttonCount == 3)
	{
		TimerCallbackTimerStart(&timerCallback, BlinkAmberLED, 100, TIMER_REPEAT);
	}
	else if(buttonCount == 4)
	{
		TimerCallbackTimerStart(&timerCallback, BlinkAmberLED, 50, TIMER_REPEAT);
	}
#endif
	// reset ButtonCount
	buttonCount = 0;
}

#endif // USE_BUTTON_COUNTER

#endif // USE_BUTTON_EXAMPLE

