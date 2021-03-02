/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Timer_Buzzer.h
**     Project     : ProjetoFinal
**     Processor   : MKL25Z128VLK4
**     Component   : FreeCntr16
**     Version     : Component 02.078, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-11-27, 08:14, # CodeGen: 0
**     Abstract    :
**         This device "FreeCntr16" implements 16-bit Free Running Counter
**     Settings    :
**         Timer name                  : TPM2_CNT (16-bit)
**         Compare name                : TPM2_MOD
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-32
**             Clock                   : 655360 Hz
**           Resolution of timer
**             microseconds            : ---
**             milliseconds            : 100
**             seconds                 : ---
**             seconds (real)          : 0.1
**             Hz                      : ---
**             kHz                     : ---
**             MHz                     : ---
**
**         Initialization:
**              Timer                  : Enabled
**
**         Timer registers
**              Counter                : TPM2_CNT  [0x4003A004]
**              Mode                   : TPM2_SC   [0x4003A000]
**              Run                    : TPM2_SC   [0x4003A000]
**              Prescaler              : TPM2_SC   [0x4003A000]
**
**         Compare registers
**              Compare                : TPM2_MOD  [0x4003A008]
**     Contents    :
**         Reset      - byte Timer_Buzzer_Reset(void);
**         GetTimeUS  - byte Timer_Buzzer_GetTimeUS(word *Time);
**         GetTimeMS  - byte Timer_Buzzer_GetTimeMS(word *Time);
**         GetTimeSec - byte Timer_Buzzer_GetTimeSec(word *Time);
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
** @file Timer_Buzzer.h
** @version 01.00
** @brief
**         This device "FreeCntr16" implements 16-bit Free Running Counter
*/         
/*!
**  @addtogroup Timer_Buzzer_module Timer_Buzzer module documentation
**  @{
*/         

#ifndef __Timer_Buzzer_H
#define __Timer_Buzzer_H

/* MODULE Timer_Buzzer. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "RealTimeLdd2.h"

#include "Cpu.h"



/*
** ===================================================================
**     Method      :  Timer_Buzzer_Reset (component FreeCntr16)
*/
/*!
**     @brief
**         This method clears the counter.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
#define Timer_Buzzer_Reset() (RealTimeLdd2_Reset(RealTimeLdd2_DeviceData))

/*
** ===================================================================
**     Method      :  Timer_Buzzer_GetTimeUS (component FreeCntr16)
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in microseconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in microseconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/
#define Timer_Buzzer_GetTimeUS(Time) (RealTimeLdd2_GetTimeUS(RealTimeLdd2_DeviceData, (uint16_t *)Time))

/*
** ===================================================================
**     Method      :  Timer_Buzzer_GetTimeMS (component FreeCntr16)
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in milliseconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in milliseconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/
#define Timer_Buzzer_GetTimeMS(Time) (RealTimeLdd2_GetTimeMS(RealTimeLdd2_DeviceData, (uint16_t *)Time))

/*
** ===================================================================
**     Method      :  Timer_Buzzer_GetTimeSec (component FreeCntr16)
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in seconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in seconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/
#define Timer_Buzzer_GetTimeSec(Time) (RealTimeLdd2_GetTimeSec(RealTimeLdd2_DeviceData, (uint16_t *)Time))

/* END Timer_Buzzer. */

#endif 
/* ifndef __Timer_Buzzer_H */
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
