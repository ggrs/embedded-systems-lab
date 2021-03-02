/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : ExtIntLdd4.c
**     Project     : ProjetoFinal
**     Processor   : MKL25Z128VLK4
**     Component   : ExtInt_LDD
**     Version     : Component 02.156, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-11-27, 08:14, # CodeGen: 0
**     Abstract    :
**         This component, "ExtInt_LDD", provide a low level API 
**         for unified access of external interrupts handling
**         across various device designs.
**         The component uses one pin which generates interrupt on 
**         selected edge.
**     Settings    :
**          Component name                                 : ExtIntLdd4
**          Pin                                            : PTD7/SPI1_MISO/UART0_TX/SPI1_MOSI
**          Pin signal                                     : 
**          Generate interrupt on                          : rising edge
**          Interrupt                                      : INT_PORTD
**          Interrupt priority                             : medium priority
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : yes
**          Threshold level                                : 0
**     Contents    :
**         Init    - LDD_TDeviceData* ExtIntLdd4_Init(LDD_TUserData *UserDataPtr);
**         GetVal  - bool ExtIntLdd4_GetVal(LDD_TDeviceData *DeviceDataPtr);
**         SetEdge - LDD_TError ExtIntLdd4_SetEdge(LDD_TDeviceData *DeviceDataPtr, uint8_t Edge);
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
** @file ExtIntLdd4.c
** @version 01.02
** @brief
**         This component, "ExtInt_LDD", provide a low level API 
**         for unified access of external interrupts handling
**         across various device designs.
**         The component uses one pin which generates interrupt on 
**         selected edge.
*/         
/*!
**  @addtogroup ExtIntLdd4_module ExtIntLdd4 module documentation
**  @{
*/         

/* MODULE ExtIntLdd4. */

#include "PIR.h"
#include "ExtIntLdd4.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TUserData *UserData;             /* RTOS device data structure */
} ExtIntLdd4_TDeviceData, *ExtIntLdd4_TDeviceDataPtr; /* Device data structure type */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static ExtIntLdd4_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static ExtIntLdd4_TDeviceData * INT_PORTD__DEFAULT_RTOS_ISRPARAM;

/*
** ===================================================================
**     Method      :  ExtIntLdd4_Init (component ExtInt_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* ExtIntLdd4_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  ExtIntLdd4_TDeviceData *DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  /* Store the UserData pointer */
  DeviceDataPrv->UserData = UserDataPtr;
  /* Interrupt vector(s) allocation */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_PORTD__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* Clear interrupt status flag */
  PORTD_ISFR = PORT_ISFR_ISF(0x80);
  /* Initialization of Port Control registers */
  /* PORTD_PCR7: ISF=0,IRQC=9,MUX=1 */
  PORTD_PCR7 = (uint32_t)((PORTD_PCR7 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_IRQC(0x06) |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_IRQC(0x09) |
                PORT_PCR_MUX(0x01)
               ));
  /* NVIC_IPR7: PRI_31=0x80 */
  NVIC_IPR7 = (uint32_t)((NVIC_IPR7 & (uint32_t)~(uint32_t)(
               NVIC_IP_PRI_31(0x7F)
              )) | (uint32_t)(
               NVIC_IP_PRI_31(0x80)
              ));
  /* NVIC_ISER: SETENA|=0x80000000 */
  NVIC_ISER |= NVIC_ISER_SETENA(0x80000000);
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_ExtIntLdd4_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}

/*
** ===================================================================
**     Method      :  ExtIntLdd4_Interrupt (component ExtInt_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(ExtIntLdd4_Interrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  ExtIntLdd4_TDeviceDataPtr DeviceDataPrv = INT_PORTD__DEFAULT_RTOS_ISRPARAM;

  /* Clear the interrupt flag */
  PORT_PDD_ClearPinInterruptFlag(PORTD_BASE_PTR, ExtIntLdd4_PIN_INDEX);
  /* Call OnInterrupt event */
  ExtIntLdd4_OnInterrupt(DeviceDataPrv->UserData);
}

/*
** ===================================================================
**     Method      :  ExtIntLdd4_GetVal (component ExtInt_LDD)
*/
/*!
**     @brief
**         Returns the actual value of the input pin of the component.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Returned input value. Possible values:
**                           <false> - logical "0" (Low level) <true> -
**                           logical "1" (High level)
*/
/* ===================================================================*/
bool ExtIntLdd4_GetVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if ((GPIO_PDD_GetPortDataInput(PTD_BASE_PTR) & ExtIntLdd4_PIN_MASK) != 0U) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*
** ===================================================================
**     Method      :  ExtIntLdd4_SetEdge (component ExtInt_LDD)
*/
/*!
**     @brief
**         Sets the edge type for this component that generates the
**         interrupt.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         Edge            - Edge type:
**                           0 - falling edge
**                           1 - rising edge
**                           2 - both edges
**                           3 - low level
**                           4 - high level
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_RANGE - Value is out of range
*/
/* ===================================================================*/
LDD_TError ExtIntLdd4_SetEdge(LDD_TDeviceData *DeviceDataPtr, uint8_t Edge)
{
  uint32_t Config;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Edge value test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (Edge > 4U) {
    return ERR_RANGE;                  /* Invalid edge parameter */
  }
  switch (Edge) {
    case 0:                            /* Falling edge */
      Config = PORT_PDD_INTERRUPT_ON_FALLING;
      break;
    case 1:                            /* Rising edge */
      Config = PORT_PDD_INTERRUPT_ON_RISING;
      break;
    case 2:                            /* Both edges */
      Config = PORT_PDD_INTERRUPT_ON_RISING_FALLING;
      break;
    case 3:                            /* Low level */
      Config = PORT_PDD_INTERRUPT_ON_ZERO;
      break;
    case 4:                            /* High level */
      Config = PORT_PDD_INTERRUPT_ON_ONE;
      break;
    default:
      return ERR_RANGE;
  }
  /* Apply the new configuration */
  PORT_PDD_SetPinInterruptConfiguration(PORTD_BASE_PTR, ExtIntLdd4_PIN_INDEX, Config);
  return ERR_OK;
}

/* END ExtIntLdd4. */

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