/*
 * ButtonCounter.h
 *
 *  Created on: Dec 26, 2022
 *      Author: codek
 */

#ifndef INC_BUTTONCOUNTER_H_
#define INC_BUTTONCOUNTER_H_


// User will need to update PushButtonPin to the actual interrupt pin name. In this case the default name B1_Pin.
#define PushButtonPin B1_Pin


void DebouncePB(void);
void ButtonCounter(void);
void ButtonCountDone(void);

#endif /* INC_BUTTONCOUNTER_H_ */
