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

volatile uint8_t br[256]; 	// buffer que armazena caracteres recebidos pelo ESP
volatile uint8_t ibr = 0;	// indice do buffer br
volatile uint8_t mr = 0; 	// variavel booleana que diz se uma mensagem foi recebida
volatile uint8_t time_counter = 2;
volatile uint8_t rtc_ready = 0;

LDD_RTC_TTime time;

// Converte valor de temperatura para uma string
void Temp_2str(uint16_t te, uint8_t *s){ 

	uint8_t c, d, u;   // centena, dezena, unidade 

	c= te/100; 
	te = te%100;
	d= te/10; 
	u= te%10; 
	// char 0 = 0x30, char 1 = 0x31, ..., char 9 = 0x39 
	*s = c + 0x30; 
	s++; 
	*s = d + 0x30; 
	s++; 
	*s = '.'; 
	s++; 
	*s = u + 0x30; 
	s++; 
	*s = 0; 
}

// Converte data e hora em string
void Time_2str(uint8_t *s){
	
	// Recebo os valores do RTC
	RTC1_GetTime(RTC1_DeviceData, &time);
	
	// Transformo em char e colocar na string
	// Data
	*s = (time.Day / 10) + 0x30;
	s++;
	*s = (time.Day % 10) + 0x30;
	s++;
	*s = '/';
	s++;
	*s = (time.Month / 10) + 0x30;
	s++;
	*s = (time.Month % 10) + 0x30;
	s++;
	*s = '/';
	s++;
	*s = (time.Year / 1000) + 0x30;
	s++;
	*s = ((time.Year % 1000) / 100) + 0x30;
	s++;
	*s = ((time.Year % 100) / 10) + 0x30;
	s++;
	*s = (time.Year % 10) + 0x30;
	s++;
	*s = ' ';
	s++;
	// Hora
	*s = (time.Hour / 10) + 0x30;
	s++;
	*s = (time.Hour % 10) + 0x30;
	s++;
	*s = ':';
	s++;
	*s = (time.Minute / 10) + 0x30;
	s++;
	*s = (time.Minute % 10) + 0x30;
	s++;
	*s = ':';
	s++;
	*s = (time.Second / 10) + 0x30;
	s++;
	*s = (time.Second % 10) + 0x30;
	s++;
	*s = ' ';
	s++;
	*s = 0;
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
	
	// ------------ Inicializacao Buffer de Mensagem --------------
	uint8_t bm[256]; // buffer que armazena as mensagens enviadas ao ESP e ao terminal
	uint8_t ibm = 0;
	uint8_t bl[25];
	uint8_t btemp[5];
	// ------------ Inicializacao Temperatura ---------------------
	uint16_t n; 
	uint16_t mv;
	int16_t tdc; 	// Temperatura em decimo de grau
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* ----------------------------- Write your code here --------------------------------- */
  
  RTC1_Enable(RTC1_DeviceData);
  
  for(;;){
	  
	  // Espero 2 segundos
	  while(!rtc_ready);
	  
	  // Conversao de Temperatura
	  (void)AD1_Measure(TRUE); 		// Faz a conversao e espera o resultado
	  (void)AD1_GetValue16(&n); 	// Coloca o resultado na variavel n
	  
	  //Converter valor em bits para mV
	  mv = (3300 * n) / 65535;
	  // Converter mV para decimo de grau
	  tdc = mv - 600;
	  // Montar string RTC
	  Time_2str(bl);
	  // Montar string Temperatura
	  Temp_2str(tdc, btemp);
	  // Montar string de envio
	  UTIL1_strcpy(bm ,256, bl);
	  UTIL1_strcat(bm, 256, btemp);
	  
	  PC_SendStr(bm);
	  
	  // Reset do rtc_ready preparando para mais 2 segundos
	  rtc_ready = 0;
	  
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
