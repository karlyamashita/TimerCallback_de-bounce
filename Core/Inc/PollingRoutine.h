/*
 * PollingInit.h
 *
 *  Created on: Dec 24, 2022
 *      Author: codek
 */

#ifndef INC_POLLINGROUTINE_H_
#define INC_POLLINGROUTINE_H_



//*********** Defines to comment/un-comment ****************
#define USE_BUTTON_EXAMPLE // un-comment to use Button examples, comment out to use examples.

#ifdef USE_BUTTON_EXAMPLE

#define NO_DEBOUNCE
//#define NORMAL_DEBOUNCE
//#define NORMAL_DEBOUNCE_BUTTON_COUNTER
//#define CHANGE_BLINK_RATE
#else // examples

//***************** Other examples **************************
#define EXAMPLE_1
//#define EXAMPLE_2
//#define EXAMPLE_3

#endif // USE_BUTTON_EXAMPLE




void PollingInit(void);
void PollingRoutine(void);



#endif /* INC_POLLINGROUTINE_H_ */
