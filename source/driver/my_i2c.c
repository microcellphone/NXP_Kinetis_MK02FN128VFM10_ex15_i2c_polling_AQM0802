/*  Standard C Included Files */
#include <string.h>
/*  SDK Included Files */
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "pin_mux.h"
#include "my_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t i2c_Config_Request(TS_I2C_INFO *i2c_data)
{
	return 0;
}


uint32_t i2c_Send_Data_Request(I2C_Type *base, uint16_t i2c_slave_address, uint8_t *snd_buff, uint32_t snd_length)
{
	i2c_master_transfer_t masterXfer;
	status_t i2c_status;

    memset(&masterXfer, 0, sizeof(masterXfer));

    /* subAddress = 0x01, data = g_master_txBuff - write to slave.
      start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/
    masterXfer.slaveAddress   = i2c_slave_address;
    masterXfer.direction      = kI2C_Write;
    masterXfer.subaddress     = (uint32_t)0;
    masterXfer.subaddressSize = 0;
    masterXfer.data           = snd_buff;
    masterXfer.dataSize       = snd_length;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    i2c_status = I2C_MasterTransferBlocking(base, &masterXfer);
    if(i2c_status != kStatus_Success) while(1);

    return snd_length;
}
