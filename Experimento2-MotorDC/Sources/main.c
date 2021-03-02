/* ###################################################################
**     Filename    : main.c
**     Project     : LAB1
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-08-14, 11:34, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */

/* Grupo I2
 * Andre Felipe Rayer Brasil 194087
 * Gustavo Graziosi Silva 169320
 */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PC.h"
#include "ASerialLdd1.h"
#include "Wifi.h"
#include "ASerialLdd2.h"
#include "MCUC1.h"
#include "UTIL1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "RTC1.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU2.h"
#include "PTE29.h"
#include "BitIoLdd1.h"
#include "PTE30.h"
#include "BitIoLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

volatile uint8_t char_rcv = 0;
uint8_t n;


void SetDC(uint8_t dc) {
	uint16_t n;
	
	// variavel dc armazena um valor de 0 a 100
	if (dc > 100) dc = 100;
	// complementar o valor para ajustar a polaridade negativa e multiplicar
	n = (100 - dc)*655;
	
	PWM1_SetRatio16(n);
}

// Funcao que envia string para o terminal
void PC_SendStr(uint8_t *s) {
	
	while(*s) {
		while(PC_SendChar(*s));
		s++;
	}
	while(PC_SendChar(0x0D));
	while(PC_SendChar(0x0A));
}

// Funcao que envia string para o modulo ESP
void Wifi_SendStr(uint8_t *s) {
	
	while(*s) {
		while(Wifi_SendChar(*s));
		s++;
	}
	while(Wifi_SendChar(0x0D));
	while(Wifi_SendChar(0x0A));
}

int main(void)

/*lint -restore Enable MISRA rule (6.3) checking. */
{
	
  /* Write your local variable definition here */
	uint8_t t; // variavel que armazena o caracter lido do terminal
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* ----------------------------- Write your code here --------------------------------- */
  
  PTE29_SetVal();
  PTE30_ClrVal();
  
  for (;;) {
	
	  if (char_rcv) {
		  PC_RecvChar(&t);
		  PC_SendChar(t);
		  if(t == 0x0D) {
			  PC_SendChar(0x0D);
			  PC_SendChar(0x0A);
			  SetDC(n);
			  n = 0;
		  } else {
			  n = n * 10;
			  n = n + (t - 0x30);
		  }
		  char_rcv = 0;
	  }
  }
  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
