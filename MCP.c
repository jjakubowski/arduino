#include <avr/io.h>

#include "MCP.h"
#include "SPI.h"
#include "util\delay.h"

/**
 * Function bit modifies a content of register
 * Function bit modifies a content of register with given data using given mask
 *
 * @param Data new data to be written
 * @param Mask Mask used for modification
 * @param Address Address of register to modify
 */

void MCPmodify(uint8_t Data, uint8_t Mask, uint8_t Address){

	SelectSlave();	//selectMCP

	SPIsend(MCP_BITMOD);		//send bit modify command
	SPIsend(Address);	//send register address
	SPIsend(Mask);		//send mask
	SPIsend(Data);		//send data
	DeselectSlave();	//deselect MCP


}
/**
 *Function returns information about tx and rx flags
 *
 * @return composed information about tx and rx flags
 *
 * @todo might be a good idea to add checking the repeated output
 */
uint8_t MCPstatus(void){

	uint8_t Byte;
	SelectSlave();	//selectMCP
	SPIsend(MCP_READ_STATUS);		//send read statud command
	Byte = SPIreceive();		//send data
	DeselectSlave();	//deselect MCP
	return Byte;

}

/**
 * Send request for content of TX buffers
 * @param Transmit_buffer Choose buffer 0,1,2 or all
 */


void MCPrequest(uint8_t Transmit_buffer){

	SelectSlave();	//selectMCP
	SPIsend(Transmit_buffer);	//define which buffers are enabled to transmit
	DeselectSlave();	//deselect MCP
}

/**
 * Function loading the TX buffer
 *
 * @param Data Pointer to data being loaded to TX buffer
 * @param Buffer Address of buffer to be loaded
 * @param length number of bytes to be loaded
 * @param OnlyData flag specifying if only data or the whole buffer is being loaded
 */
void MCPloadTX(uint8_t *Data, uint8_t Buffer,uint8_t length, uint8_t OnlyData){


	SelectSlave();	//selectMCP
	SPIsend( Buffer | ( OnlyData) );	//send write address
	while(length)
	{
		
		SPIsend(*Data);		//send data
		Data++;
		length--;
	}
	DeselectSlave();	//deselect MCP

}


/**
 *Basic function writing to MCP2515
 *
 *@param Data Data to be written
 *@param Address Address where the data should be written
 */
void MCPwrite(uint8_t Data, uint8_t Address){

	SelectSlave();	//selectMCP
	SPIsend(MCP_WRITE);		//send write command
	SPIsend(Address);	//send write address
	
	SPIsend(Data);		//send data
	DeselectSlave();	//deselect MCP

}

/**
 * Function reading from MCP2515 RX buffer
 *
 * Function reads given RX buffer. SPI overhead is minimzed by not using specifying address in seperate byte.\
 * After read operation RX buffer flag is cleared
 *
 *
 * @param Data pointer to place where buffer content will be stored
 * @param Buffer address of buffer being read
 * @param start_point flag if the whole buffer is read or only data_bytes
 */
void MCPreadRX(uint8_t *Data, uint8_t Buffer,uint8_t start_point){

	uint8_t Byte;
	int i;
	int length;
	
	SelectSlave();	//selectMCP
	SPIsend(Buffer | ( start_point <<1));
	
	if (start_point) length = 8;
	else length = 13;
	
	for(i=0;i<length;i++)
	{
		*Data=SPIreceive();
		Data++;
	}
	
	DeselectSlave();	//deselect MCP
	

}

/**
 * Basic function reading from MCP2515
 *
 * @param Address Address of register being read
 *
 * @return content of the read register
 */
uint8_t MCPread(uint8_t Address){

	uint8_t Byte;

	SelectSlave();	//selectMCP
	SPIsend(MCP_READ);		//send reading command
	SPIsend(Address);	//send address
	Byte = SPIreceive();//read byte
	DeselectSlave();	//deselect MCP
	return Byte;

}


/**
 * Function resetting content of all MCP2515 registers
 */
void MCPreset(void){

	SelectSlave();	//select MCP
	SPIsend(MCP_RESET);		//send RESET vector
	_delay_ms(1);
	DeselectSlave();	//deselect MCP

}

