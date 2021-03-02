/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : CI2C1.c
**     Project     : ProjetoFinal
**     Processor   : MKL25Z128VLK4
**     Component   : I2C_LDD
**     Version     : Component 01.016, Driver 01.07, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-11-27, 08:14, # CodeGen: 0
**     Abstract    :
**          This component encapsulates the internal I2C communication
**          interface. The implementation of the interface is based
**          on the Philips I2C-bus specification version 2.0.
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible
**              (see SendStop parameter in MasterSend/ReceiveBlock method)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
**     Settings    :
**          Component name                                 : CI2C1
**          I2C channel                                    : I2C1
**          Interrupt service                              : Enabled
**            Interrupt                                    : INT_I2C1
**            Interrupt priority                           : medium priority
**          Settings                                       : 
**            Mode selection                               : MASTER
**            MASTER mode                                  : Enabled
**              Initialization                             : 
**                Address mode                             : 7-bit addressing
**                Target slave address init                : 0
**            SLAVE mode                                   : Disabled
**            Pins                                         : 
**              SDA pin                                    : 
**                SDA pin                                  : PTC11/I2C1_SDA
**                SDA pin signal                           : 
**              SCL pin                                    : 
**                SCL pin                                  : PTC10/I2C1_SCL
**                SCL pin signal                           : 
**              High drive select                          : Disabled
**              Input Glitch filter                        : 0
**            Internal frequency (multiplier factor)       : 20.97152 MHz
**            Bits 0-2 of Frequency divider register       : 001
**            Bits 3-5 of Frequency divider register       : 010
**            SCL frequency                                : 374.491 kHz
**            SDA Hold                                     : 0.429 us
**            SCL start Hold                               : 1.049 us
**            SCL stop Hold                                : 1.383 us
**            Control acknowledge bit                      : Disabled
**            Low timeout                                  : Disabled
**          Initialization                                 : 
**            Enabled in init code                         : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnMasterBlockSent                          : Enabled
**              OnMasterBlockReceived                      : Enabled
**              OnMasterByteReceived                       : Disabled
**              OnSlaveBlockSent                           : Disabled
**              OnSlaveBlockReceived                       : Disabled
**              OnSlaveByteReceived                        : Disabled
**              OnSlaveRxRequest                           : Disabled
**              OnSlaveTxRequest                           : Disabled
**              OnSlaveGeneralCallAddr                     : Disabled
**              OnSlaveSmBusCallAddr                       : Disabled
**              OnSlaveSmBusAlertResponse                  : Disabled
**              OnError                                    : Disabled
**              OnBusStopDetected                          : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init               - LDD_TDeviceData* CI2C1_Init(LDD_TUserData *UserDataPtr);
**         Deinit             - void CI2C1_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         MasterSendBlock    - LDD_TError CI2C1_MasterSendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         MasterReceiveBlock - LDD_TError CI2C1_MasterReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         SelectSlaveDevice  - LDD_TError CI2C1_SelectSlaveDevice(LDD_TDeviceData *DeviceDataPtr,...
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file CI2C1.c
** @version 01.07
** @brief
**          This component encapsulates the internal I2C communication
**          interface. The implementation of the interface is based
**          on the Philips I2C-bus specification version 2.0.
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible
**              (see SendStop parameter in MasterSend/ReceiveBlock method)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
*/         
/*!
**  @addtogroup CI2C1_module CI2C1 module documentation
**  @{
*/         

/* MODULE CI2C1. */

#include "GI2C1.h"
#include "CI2C1.h"
#include "PORT_PDD.h"
#include "I2C_PDD.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* SerFlag bits */
#define MASTER_IN_PROGRES       0x01U  /* Communication is in progress (Master) */
#define ADDR_COMPLETE           0x02U  /* 10-bit address transmission complete   */
#define REP_ADDR_COMPLETE       0x04U  /* repeated address transmission complete */
#define GENERAL_CALL            0x08U  /* General call flag */
#define ADDR_10                 0x10U  /* 10-bit addr flag */
#define ADDR_7                  0x20U  /* 7-bit addr flag */

typedef struct {
  uint8_t SerFlag;                     /* Flags for serial communication */
                                       /* Bits: 0 - Running int from TX */
                                       /*       1 - 10-bit address transmission complete   */
                                       /*       2 - repeated address transmission complete */
                                       /*       3 - General Call flag */
                                       /*       4 - 10-bit addr flag */
                                       /*       5 - 7-bit addr flag */
  LDD_I2C_TSendStop SendStop;          /* Enable/Disable generate send stop condition after transmission */
  uint8_t SlaveAddr;                   /* Variable for Slave address */
  uint8_t SlaveAddrHigh;               /* Variable for High byte of the Slave address (10-bit address) */
  LDD_I2C_TSize InpLenM;               /* The counter of input bufer's content */
  uint8_t *InpPtrM;                    /* Pointer to input buffer for Master mode */
  LDD_I2C_TSize OutLenM;               /* The counter of output bufer's content */
  uint8_t *OutPtrM;                    /* Pointer to output buffer for Master mode */
  LDD_TUserData *UserData;             /* RTOS device data structure */
} CI2C1_TDeviceData;

typedef CI2C1_TDeviceData *CI2C1_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static CI2C1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static CI2C1_TDeviceDataPtr INT_I2C1__DEFAULT_RTOS_ISRPARAM;

#define AVAILABLE_EVENTS_MASK (LDD_I2C_ON_MASTER_BLOCK_SENT | LDD_I2C_ON_MASTER_BLOCK_RECEIVED)

/*
** ===================================================================
**     Method      :  CI2C1_Interrupt (component I2C_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

PE_ISR(CI2C1_Interrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  CI2C1_TDeviceDataPtr DeviceDataPrv = INT_I2C1__DEFAULT_RTOS_ISRPARAM;
  register uint8_t Status;             /* Temporary variable for status register */

  Status = I2C_PDD_ReadStatusReg(I2C1_BASE_PTR); /* Safe status register */
  I2C_PDD_ClearInterruptFlags(I2C1_BASE_PTR, (Status)); /* Clear interrupt flag */
  if (I2C_PDD_GetMasterMode(I2C1_BASE_PTR) == I2C_PDD_MASTER_MODE) { /* Is device in master mode? */
    if (I2C_PDD_GetTransmitMode(I2C1_BASE_PTR) == I2C_PDD_TX_DIRECTION) { /* Is device in Tx mode? */
      if ((Status & I2C_PDD_RX_ACKNOWLEDGE) != 0x00U){ /* NACK received? */
        I2C_PDD_SetMasterMode(I2C1_BASE_PTR, I2C_PDD_SLAVE_MODE); /* Switch device to slave mode (stop signal sent) */
        I2C_PDD_SetTransmitMode(I2C1_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
        DeviceDataPrv->OutLenM = 0x00U; /* No character for sending */
        DeviceDataPrv->InpLenM = 0x00U; /* No character for reception */
        DeviceDataPrv->SerFlag &= (uint8_t)~(MASTER_IN_PROGRES); /* No character for sending or reception */
        DeviceDataPrv->SerFlag |= (ADDR_COMPLETE | REP_ADDR_COMPLETE); /* Set the flag */
      } else {
        if ((DeviceDataPrv->SerFlag & ADDR_COMPLETE) != 0x00U) { /* If 10-bit addr has been completed */
          if (DeviceDataPrv->OutLenM != 0x00U) { /* Is any char. for transmitting? */
            DeviceDataPrv->OutLenM--;  /* Decrease number of chars for the transmit */
            I2C_PDD_WriteDataReg(I2C1_BASE_PTR, *(DeviceDataPrv->OutPtrM)++); /* Send character */
          } else {
            if (DeviceDataPrv->InpLenM != 0x00U) { /* Is any char. for reception? */
              if ((DeviceDataPrv->SerFlag & REP_ADDR_COMPLETE) != 0x00U) { /* If repeated start and addr tx has been completed for 10-bit mode ?*/
                if (DeviceDataPrv->InpLenM == 0x01U) { /* If only one char to receive */
                  I2C_PDD_EnableTransmitAcknowledge(I2C1_BASE_PTR, PDD_DISABLE); /* then transmit ACK disable */
                } else {
                  I2C_PDD_EnableTransmitAcknowledge(I2C1_BASE_PTR, PDD_ENABLE); /* else transmit ACK enable */
                }
                I2C_PDD_SetTransmitMode(I2C1_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
                (void)I2C_PDD_ReadDataReg(I2C1_BASE_PTR); /* Dummy read character */
              } else {                 /* Repeated address has not been completed for 10-bit addressing mode */
                I2C_PDD_RepeatStart(I2C1_BASE_PTR); /* Repeat start cycle generated */
                I2C_PDD_WriteDataReg(I2C1_BASE_PTR, (uint8_t)(DeviceDataPrv->SlaveAddrHigh | 0x01U)); /* Send slave address high byte*/
                DeviceDataPrv->SerFlag |= REP_ADDR_COMPLETE;
              }
            } else {
              DeviceDataPrv->SerFlag &= (uint8_t)~(MASTER_IN_PROGRES); /* Clear flag "busy" */
              if (DeviceDataPrv->SendStop == LDD_I2C_SEND_STOP) {
                I2C_PDD_SetMasterMode(I2C1_BASE_PTR, I2C_PDD_SLAVE_MODE); /* Switch device to slave mode (stop signal sent) */
                I2C_PDD_SetTransmitMode(I2C1_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
              }
              CI2C1_OnMasterBlockSent(DeviceDataPrv->UserData); /* Invoke OnMasterBlockSent event */
            }
          }
        } else {
          I2C_PDD_WriteDataReg(I2C1_BASE_PTR, DeviceDataPrv->SlaveAddr); /* Send second part of the 10-bit addres */
          DeviceDataPrv->SerFlag |= (ADDR_COMPLETE); /* Address complete */
        }
      }
    } else {
      DeviceDataPrv->InpLenM--;        /* Decrease number of chars for the receive */
      if (DeviceDataPrv->InpLenM != 0x00U) { /* Is any char. for reception? */
        if (DeviceDataPrv->InpLenM == 0x01U) {
          I2C_PDD_EnableTransmitAcknowledge(I2C1_BASE_PTR, PDD_DISABLE); /* Transmit NACK */
        }
      } else {
        DeviceDataPrv->SerFlag &= (uint8_t)~(MASTER_IN_PROGRES); /* Clear flag "busy" */
        I2C_PDD_SetMasterMode(I2C1_BASE_PTR, I2C_PDD_SLAVE_MODE); /* If no, switch device to slave mode (stop signal sent) */
        I2C_PDD_EnableTransmitAcknowledge(I2C1_BASE_PTR, PDD_ENABLE); /* Transmit ACK */
      }
      *(DeviceDataPrv->InpPtrM)++ = I2C_PDD_ReadDataReg(I2C1_BASE_PTR); /* Receive character */
      if (DeviceDataPrv->InpLenM == 0x00U) { /* Is any char. for reception? */
        CI2C1_OnMasterBlockReceived(DeviceDataPrv->UserData); /* Invoke OnMasterBlockReceived event */
      }
    }
  } else {
    if ((Status & I2C_PDD_ARBIT_LOST) != 0x00U) { /* Arbitration lost? */
      DeviceDataPrv->OutLenM = 0x00U;  /* Any character is not for sent */
      DeviceDataPrv->InpLenM = 0x00U;  /* Any character is not for reception */
      DeviceDataPrv->SendStop = LDD_I2C_SEND_STOP; /* Set variable for sending stop condition (for master mode) */
      DeviceDataPrv->SerFlag &= (uint8_t)~(MASTER_IN_PROGRES); /* Any character is not for sent or reception*/
      I2C_PDD_SetTransmitMode(I2C1_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
    }
  }
}

/*
** ===================================================================
**     Method      :  CI2C1_Init (component I2C_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc.
**         If the "Enable in init. code" is set to "yes" value then the
**         device is also enabled(see the description of the Enable()
**         method). In this case the Enable() method is not necessary
**         and needn't to be generated. 
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the device data structure. 
*/
/* ===================================================================*/
LDD_TDeviceData* CI2C1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate HAL device structure */
  CI2C1_TDeviceData *DeviceDataPrv;
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;

  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */

  /* Allocate interrupt vector */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_I2C1__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  DeviceDataPrv->SerFlag = ADDR_7;     /* Reset all flags start with 7-bit address mode */
  DeviceDataPrv->SlaveAddr = 0x00U;    /* Set variable for slave address */
  DeviceDataPrv->SendStop = LDD_I2C_SEND_STOP; /* Set variable for sending stop condition (for master mode) */
  DeviceDataPrv->InpLenM = 0x00U;      /* Set zero counter of data of reception */
  DeviceDataPrv->OutLenM = 0x00U;      /* Set zero counter of data of transmission */
  /* SIM_SCGC4: I2C1=1 */
  SIM_SCGC4 |= SIM_SCGC4_I2C1_MASK;
  /* I2C1_C1: IICEN=0,IICIE=0,MST=0,TX=0,TXAK=0,RSTA=0,WUEN=0,DMAEN=0 */
  I2C1_C1 = 0x00U;                     /* Clear control register */
  /* I2C1_FLT: SHEN=0,STOPF=1,STOPIE=0,FLT=0 */
  I2C1_FLT = (I2C_FLT_STOPF_MASK | I2C_FLT_FLT(0x00)); /* Clear bus status interrupt flags */
  /* I2C1_S: TCF=0,IAAS=0,BUSY=0,ARBL=0,RAM=0,SRW=0,IICIF=1,RXAK=0 */
  I2C1_S = I2C_S_IICIF_MASK;           /* Clear interrupt flag */
  /* PORTC_PCR11: ISF=0,MUX=2 */
  PORTC_PCR11 = (uint32_t)((PORTC_PCR11 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x05)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x02)
                ));
  /* PORTC_PCR10: ISF=0,MUX=2 */
  PORTC_PCR10 = (uint32_t)((PORTC_PCR10 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x05)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x02)
                ));
  /* NVIC_IPR2: PRI_9=0x80 */
  NVIC_IPR2 = (uint32_t)((NVIC_IPR2 & (uint32_t)~(uint32_t)(
               NVIC_IP_PRI_9(0x7F)
              )) | (uint32_t)(
               NVIC_IP_PRI_9(0x80)
              ));
  /* NVIC_ISER: SETENA|=0x0200 */
  NVIC_ISER |= NVIC_ISER_SETENA(0x0200);
  /* I2C1_C2: GCAEN=0,ADEXT=0,HDRS=0,SBRC=0,RMEN=0,AD=0 */
  I2C1_C2 = I2C_C2_AD(0x00);
  /* I2C1_FLT: SHEN=0,STOPF=0,STOPIE=0,FLT=0 */
  I2C1_FLT = I2C_FLT_FLT(0x00);        /* Set glitch filter register */
  /* I2C1_SMB: FACK=0,ALERTEN=0,SIICAEN=0,TCKSEL=0,SLTF=1,SHTF1=0,SHTF2=0,SHTF2IE=0 */
  I2C1_SMB = I2C_SMB_SLTF_MASK;
  /* I2C1_F: MULT=0,ICR=0x11 */
  I2C1_F = (I2C_F_MULT(0x00) | I2C_F_ICR(0x11)); /* Set prescaler bits */
  I2C_PDD_EnableDevice(I2C1_BASE_PTR, PDD_ENABLE); /* Enable device */
  I2C_PDD_EnableInterrupt(I2C1_BASE_PTR); /* Enable interrupt */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_CI2C1_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the data data structure */
}

/*
** ===================================================================
**     Method      :  CI2C1_Deinit (component I2C_LDD)
*/
/*!
**     @brief
**         Deinitializes the device. Switches off the device, frees the
**         device data structure memory, interrupts vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
*/
/* ===================================================================*/
void CI2C1_Deinit(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */

  /* I2C1_C1: IICEN=0,IICIE=0,MST=0,TX=0,TXAK=0,RSTA=0,WUEN=0,DMAEN=0 */
  I2C1_C1 = 0x00U;                     /* Reset I2C Control register */
  /* Restoring the interrupt vector */
  /* {Default RTOS Adapter} Restore interrupt vector: IVT is static, no code is generated */
  /* Unregistration of the device structure */
  PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_CI2C1_ID);
  /* Deallocation of the device structure */
  /* {Default RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
  /* SIM_SCGC4: I2C1=0 */
  SIM_SCGC4 &= (uint32_t)~(uint32_t)(SIM_SCGC4_I2C1_MASK);
}

/*
** ===================================================================
**     Method      :  CI2C1_MasterSendBlock (component I2C_LDD)
*/
/*!
**     @brief
**         This method writes one (7-bit addressing) or two (10-bit
**         addressing) slave address bytes inclusive of R/W bit = 0 to
**         the I2C bus and then writes the block of characters to the
**         bus. The slave address must be specified before, by the
**         "SelectSlaveDevice" method or in component initialization
**         section, "Target slave address init" property. If the method
**         returns ERR_OK, it doesn't mean that transmission was
**         successful. The state of transmission is detectable by means
**         of events (OnMasterSendComplete or OnError). Data to be sent
**         are not copied to an internal buffer and remains in the
**         original location. Therefore the content of the buffer
**         should not be changed until the transmission is complete.
**         Event "OnMasterBlockSent"can be used to detect the end of
**         the transmission. This method is available only for the
**         MASTER or MASTER - SLAVE mode.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BufferPtr       - Pointer to the block of data
**                           to send.
**     @param
**         Size            - Size of the data block.
**     @param
**         SendStop        - Parameter for generating I2C
**                           Stop condition
**                           LDD_I2C_SEND_STOP - Stop condition is
**                           generated on end transmission.
**                           LDD_I2C_NO_SEND_STOP - Stop condition isn't
**                           generated on end transmission.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - The I2C device is now running
*/
/* ===================================================================*/
LDD_TError CI2C1_MasterSendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, LDD_I2C_TSize Size, LDD_I2C_TSendStop SendStop)
{
  CI2C1_TDeviceData *DeviceDataPrv = (CI2C1_TDeviceData *)DeviceDataPtr;

  if (Size == 0x00U) {                 /* Test variable Size on zero */
    return ERR_OK;                     /* If zero then OK */
  }
  if (DeviceDataPrv->SendStop == LDD_I2C_SEND_STOP) {
    if ((I2C_PDD_GetBusStatus(I2C1_BASE_PTR) == I2C_PDD_BUS_BUSY) || /* Is the bus busy? */  \
       ((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) || \
       (DeviceDataPrv->OutLenM != 0x00U))  {
      return ERR_BUSY;                 /* If yes then error */
    }
  } else {
    if (((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) || /* Is the bus busy? */  \
      (DeviceDataPrv->OutLenM != 0x00U))  {
      return ERR_BUSY;                 /* If yes then error */
    }
  }
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  DeviceDataPrv->SerFlag |= MASTER_IN_PROGRES; /* Set flag "busy" */
  DeviceDataPrv->OutPtrM = (uint8_t *)BufferPtr; /* Save pointer to data for transmitting */
  DeviceDataPrv->OutLenM = Size;       /* Set the counter of output bufer's content */
  DeviceDataPrv->SendStop = SendStop;  /* Set generating stop condition */
  I2C_PDD_SetTransmitMode(I2C1_BASE_PTR, I2C_PDD_TX_DIRECTION); /* Set TX mode */
  if (I2C_PDD_GetMasterMode(I2C1_BASE_PTR) == I2C_PDD_MASTER_MODE) { /* Is device in master mode? */
    I2C_PDD_RepeatStart(I2C1_BASE_PTR); /* If yes then repeat start cycle generated */
  } else {
    I2C_PDD_SetMasterMode(I2C1_BASE_PTR, I2C_PDD_MASTER_MODE); /* If no then start signal generated */
  }
  if ((DeviceDataPrv->SerFlag & ADDR_7) != 0x00U) { /* Is 7-bit addressing set ? */
    DeviceDataPrv->SerFlag |= (ADDR_COMPLETE | REP_ADDR_COMPLETE); /* Only one byte of address will be sent 7-bit address mode*/
    I2C_PDD_WriteDataReg(I2C1_BASE_PTR, DeviceDataPrv->SlaveAddr); /* Send slave address */
  } else {
    if ((DeviceDataPrv->SerFlag & ADDR_10) != 0x00U) { /* Is 10-bit addressing set ? */
      DeviceDataPrv->SerFlag &= (uint8_t)~(ADDR_COMPLETE | REP_ADDR_COMPLETE); /* Second byte of address will be sent later */
      I2C_PDD_WriteDataReg(I2C1_BASE_PTR, DeviceDataPrv->SlaveAddrHigh); /* Send slave address - high byte */
    } else {
      if ((DeviceDataPrv->SerFlag & GENERAL_CALL) != 0x00U) { /* Is general call command required ? */
        DeviceDataPrv->SerFlag |= ADDR_COMPLETE; /* Only one byte of address will be sent in general call address mode*/
        I2C_PDD_WriteDataReg(I2C1_BASE_PTR, 0x00U); /* Send general call address */
      }
    }
  }
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CI2C1_MasterReceiveBlock (component I2C_LDD)
*/
/*!
**     @brief
**         This method writes one (7-bit addressing) or two (10-bit
**         addressing) slave address bytes inclusive of R/W bit = 1 to
**         the I2C bus and then receives the block of characters from
**         the bus. The slave address must be specified before, by the
**         "SelectSlaveDevice" method or in component initialization
**         section, "Target slave address init" property. If the method
**         returns ERR_OK, it doesn't mean that reception was
**         successful. The state of reception is detectable by means of
**         events (OnMasterSendComplete  or OnError). Data to be
**         received are not copied to an internal buffer and remains in
**         the original location. Therefore the content of the buffer
**         should not be changed until the transmission is complete.
**         Event "OnMasterBlockReceived"can be used to detect the end
**         of the reception. This method is available only for the
**         MASTER or MASTER - SLAVE mode.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BufferPtr       - Pointer to a buffer where
**                           received characters will be stored.
**     @param
**         Size            - The size of the block.
**     @param
**         SendStop        - Parameter for generating I2C
**                           Stop condition
**                           LDD_I2C_SEND_STOP - Stop condition is
**                           generated on end transmission.
**                           LDD_I2C_NO_SEND_STOP - Stop condition isn't
**                           generated on end transmission.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - The master device is busy
**                           ERR_NOTAVAIL - It is not possible to
**                           receive data if general call address is set.
**                           ERR_PARAM_MODE -  Stop condition isn't
**                           possible generated on end transmission.
*/
/* ===================================================================*/
LDD_TError CI2C1_MasterReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, LDD_I2C_TSize Size, LDD_I2C_TSendStop SendStop)
{
  CI2C1_TDeviceData *DeviceDataPrv = (CI2C1_TDeviceData *)DeviceDataPtr;

  if (Size == 0x00U) {                 /* Test variable Size on zero */
    return ERR_OK;                     /* If zero then OK */
  }
  if (SendStop == LDD_I2C_NO_SEND_STOP) { /* Test variable SendStop on supported value */
    return ERR_PARAM_MODE;             /* If not supported value then error */
  }
  if ((DeviceDataPrv->SerFlag & GENERAL_CALL) != 0x00U) { /* Is the general call flag set (SelectSlaveDevice - address type is general call) ? */
    return ERR_NOTAVAIL;               /* It is not possible to receive data - Call SelectSlaveDevice method */
  }
  if (DeviceDataPrv->SendStop == LDD_I2C_SEND_STOP) {
    if ((I2C_PDD_GetBusStatus(I2C1_BASE_PTR) == I2C_PDD_BUS_BUSY) || /* Is the bus busy? */  \
      ((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) || \
      (DeviceDataPrv->InpLenM != 0x00U)) {
      return ERR_BUSY;                 /* If yes then error */
    }
  } else {
    if(((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) || /* Is the bus busy? */  \
      (DeviceDataPrv->InpLenM != 0x00U)) {
      return ERR_BUSY;               /* If yes then error */
    }
  }
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  DeviceDataPrv->SerFlag |= MASTER_IN_PROGRES; /* Set flag "busy" */
  DeviceDataPrv->InpPtrM = (uint8_t *)BufferPtr; /* Save pointer to data for reception */
  DeviceDataPrv->InpLenM = Size;       /* Set the counter of input bufer's content */
  DeviceDataPrv->SendStop = SendStop;  /* Set generating stop condition */
  I2C_PDD_SetTransmitMode(I2C1_BASE_PTR, I2C_PDD_TX_DIRECTION); /* Set TX mode */
  if (I2C_PDD_GetMasterMode(I2C1_BASE_PTR) == I2C_PDD_MASTER_MODE) { /* Is device in master mode? */
    I2C_PDD_RepeatStart(I2C1_BASE_PTR); /* If yes then repeat start cycle generated */
  } else {
    I2C_PDD_SetMasterMode(I2C1_BASE_PTR, I2C_PDD_MASTER_MODE); /* If no then start signal generated */
  }
  if ((DeviceDataPrv->SerFlag & ADDR_7) != 0x00U) { /* Is 7-bit addressing set ? */
    DeviceDataPrv->SerFlag |= (ADDR_COMPLETE|REP_ADDR_COMPLETE); /* Only one byte of address will be sent 7-bit address mode*/
    I2C_PDD_WriteDataReg(I2C1_BASE_PTR, (uint8_t)(DeviceDataPrv->SlaveAddr | 0x01U)); /* Send slave address */
  } else {
    if ((DeviceDataPrv->SerFlag & ADDR_10) != 0x00U) { /* Is 10-bit addressing set ? */
      DeviceDataPrv->SerFlag &= (uint8_t)~(ADDR_COMPLETE | REP_ADDR_COMPLETE); /* Second byte of address will be sent later */
      I2C_PDD_WriteDataReg(I2C1_BASE_PTR, DeviceDataPrv->SlaveAddrHigh); /* Send slave address - high byte */
    }
  }
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CI2C1_SelectSlaveDevice (component I2C_LDD)
*/
/*!
**     @brief
**         This method selects a new slave for communication by its
**         7-bit slave, 10-bit address or general call value. Any send
**         or receive method directs to or from selected device, until
**         a new slave device is selected by this method. This method
**         is available for the MASTER mode.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         AddrType        - Specify type of slave address
**                           (7bit, 10bit or general call address), e.g.
**                           LDD_I2C_ADDRTYPE_7BITS.
**     @param
**         Addr            - 7bit or 10bit slave address value.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_BUSY - The device is busy, wait until
**                           the current operation is finished.
**                           ERR_DISABLED -  The device is disabled.
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_PARAM_ADDRESS_TYPE -  Invalid address
**                           type.
**                           ERR_PARAM_ADDRESS -  Invalid address value.
*/
/* ===================================================================*/
LDD_TError CI2C1_SelectSlaveDevice(LDD_TDeviceData *DeviceDataPtr, LDD_I2C_TAddrType AddrType, LDD_I2C_TAddr Addr)
{
  CI2C1_TDeviceData *DeviceDataPrv = (CI2C1_TDeviceData *)DeviceDataPtr;

  if ((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) { /* Is the device in the active state? */
    return ERR_BUSY;                   /* If yes then error */
  }
  switch (AddrType) {
    case LDD_I2C_ADDRTYPE_7BITS:
      if (Addr > 0x7FU) {              /* Test address value */
        return ERR_PARAM_ADDRESS;      /* If value of address is invalid, return error */
      }
      DeviceDataPrv->SlaveAddr = (uint8_t)((uint8_t)Addr << 0x01U); /* Set slave address */
      DeviceDataPrv->SerFlag &= (uint8_t)~(GENERAL_CALL | ADDR_10); /* Clear the general call flag and 10-bit address mode flag */
      DeviceDataPrv->SerFlag |= ADDR_7; /* Set 7-bit address mode flag */
    break;
    case LDD_I2C_ADDRTYPE_10BITS:
      if (Addr > 0x03FFU) {            /* Test address value */
        return ERR_PARAM_ADDRESS;      /* If value of address is invalid, return error */
      }
      DeviceDataPrv->SlaveAddr = (uint8_t)Addr; /* Set slave address - low byte */
      DeviceDataPrv->SlaveAddrHigh = (uint8_t)((uint16_t)Addr >> 0x07U); /* Set slave address - high byte*/
      DeviceDataPrv->SlaveAddrHigh &= 0x06U; /* Format address to 11110xx0 */
      DeviceDataPrv->SlaveAddrHigh |= 0xF0U;
      DeviceDataPrv->SerFlag &= (uint8_t)~(GENERAL_CALL | ADDR_7); /* Clear the general call flag and 7-bit address mode flag */
      DeviceDataPrv->SerFlag |= ADDR_10; /* Set 10-bit address mode flag */
    break;
    case LDD_I2C_ADDRTYPE_GENERAL_CALL:
      DeviceDataPrv->SerFlag &= (uint8_t)~(ADDR_7 | ADDR_10); /* Clear the 7-bit address flag and 10-bit address mode flag */
      DeviceDataPrv->SerFlag |= GENERAL_CALL; /* Set general call mode flag */
    break;
    default:
      return ERR_PARAM_ADDRESS_TYPE;   /* If value of address type is invalid, return error */
  }
  return ERR_OK;                       /* OK */
}

/* END CI2C1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
