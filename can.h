/*
 * can.h
 *
 *  Created on: 14 paü 2014
 *      Author: Jakub
 */

#ifndef CAN_H_
#define CAN_H_

#include "avr/io.h"


#define ONLY_DATA 1
#define NONE 0

#define BUFFER_0 0
#define BUFFER_1 1
#define BUFFER_2 2


typedef struct{
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
} can_message_t;


uint8_t CanInit(void);
void CanSendMsg(can_message_t* message,uint8_t buffer);
void CanReceiveMsg(can_message_t *message,uint8_t buffer);
void CanChangeBufferPriority(uint8_t buffer, uint8_t priority);
#endif /* CAN_H_ */
