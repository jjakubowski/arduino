#include "Can.h"
#include "mcp.h"
#include "Spi.h"
#include "ExtInt.h"
#include <avr/io.h>


// Macro for easier calculating of address of further buffers
#define BUFFER_OFFSET(REGISTER,BUFFER_NUMBER) (REGISTER + BUFFER_NUMBER*0x10)

/**
 *Initialization of CAN Interface.
 *Initialization of CAN Interface and all layers below
 *
 *@return -1 in case of failure, 0 otherwise
 */
uint8_t CanInit(void)
{

	uint8_t value;

	SPIinit();
	MCPreset();
	ExtIntInit();

	value = MCPread(MCP_CANSTAT);

	if((value & MODE_MASK) != MODE_CONFIG)
	{
	//	printf("Eror - MCP2515 NOT in config mode after rst! \n\r");
		return -1;
	}
	MCPmodify(MODE_NORMAL, MODE_MASK, MCP_CANCTRL);
	
	MCPwrite(MCP_RX_INT, MCP_CANINTE);
	DeselectSlave();


	return 0;
}


/**
 * TX CAN function
 * Function sends a message through one of TX buffers with given priority.
 *
 * @param message address to CAN type message
 * @param buffer  buffer number(0,1,2)
 */
void CanSendMsg(can_message_t* message,uint8_t buffer)
{
	uint8_t block[] = {(uint8_t) (message->id >> 3), (uint8_t) (message->id <<5), 0x00, 0x00, message->length};


	MCPloadTX(block, MCP_LOAD_TX0+buffer*2, 5, NONE);
	MCPloadTX(message->data, MCP_LOAD_TX0+buffer*2, message->length, ONLY_DATA);
	
	MCPrequest(MCP_RTS | (1<<buffer) );
}

/**
 * RX CAN function
 * Function receives a message from one of RX buffers
 *
 * @param message address to CAN type message
 * @param buffer  buffer number(0,1)
 */
void CanReceiveMsg(can_message_t *message,uint8_t buffer)
{
	
	uint8_t temp[13];
	int i;
	
	
	MCPreadRX(temp, MCP_READ_RX0+buffer*4,NONE);
	
	message->id = (temp[0]<<3) | (temp[1] >>5 );
	message->length = (temp[4] & 0x0F );
	
	for(i=0;i<message->length;i++)
	{
		message->data[i] = temp[i+5];	
	}
	
}
/**
 * Changes the buffer priority.
 *
 * @param buffer buffer number(0,1,2)
 * @param priority given priority (0,1,2,3)
 */
void CanChangeBufferPriority(uint8_t buffer, uint8_t priority)
{
	MCPwrite(priority,BUFFER_OFFSET(MCP_TXB0CTRL, buffer));
}




