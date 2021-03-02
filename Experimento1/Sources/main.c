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
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

volatile uint8_t br[256]; // buffer que armazena caracteres recebidos pelo ESP
volatile uint8_t ibr = 0; // indice do buffer br
volatile uint8_t mr = 0; // variavel booleana que diz se uma mensagem foi recebida


void PC_SendStr(uint8_t *s) {
	
	while(*s) {
		while(PC_SendChar(*s));
		s++;
	}
	while(PC_SendChar(0x0D));
	while(PC_SendChar(0x0A));
}

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
	uint8_t c;
	uint8_t bm[256]; // buffer que armazena as mensagens enviadas ao ESP e ao terminal
	uint8_t conectado = 0;
	uint8_t bt[256]; // buffer que armazena as mensagens do terminal
	uint8_t ibt = 0;
	uint8_t btopico[256], btexto[256];
	int8_t found = 0;
	uint8_t k = 0;
	uint8_t l = 0;
	uint8_t error1, error2;
	int8_t error = 0;
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  
  // 1) Connect Wifi ------------------------------------------------------
  UTIL1_strcpy(bm,256,"CONNWIFI \"EA076R\",\"FRDMKL25\"");
  
  //PC_SendStr(bm);
  
  while (!conectado) {
	  Wifi_SendStr(bm);
	  while(!mr);
	  if(!UTIL1_strcmp(br,"CONNECT WIFI")) {
		  conectado = 1;
	  }
  }
  mr = 0;
  //PC_SendStr(br);
  
  // 2) Get MAC -------------------------------------------------------
  UTIL1_strcpy(bm,256,"GETMAC");
  //PC_SendStr(bm);
  
  Wifi_SendStr(bm);
  while (!mr);
  mr = 0;
  //PC_SendStr(br);
  
  // 3) Connect MQTT ------------------------------------------------------
  UTIL1_strcpy(bm,256,"CONNMQTT \"192.168.1.111\",1883,\"");
  UTIL1_strcat(bm,256,br);
  UTIL1_strcat(bm,256,"\",\"aluno\",\"UNICAMP\"");
  conectado = 0;
  //PC_SendStr(bm);
	
  while (!conectado) {
	  Wifi_SendStr(bm);
	  while(!mr);
	  if(!UTIL1_strcmp(br,"CONNECT MQTT")) {
		  conectado = 1;
	  }
  }
  mr = 0;
  //PC_SendStr(br);
	
  // 4) Subscribe ------------------------------------------------------
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/celular\"");
	  
  //PC_SendStr(bm);
  conectado = 0;
  while (!conectado) {
	  Wifi_SendStr(bm);
	  while(!mr);
	  if(!UTIL1_strcmp(br,"OK SUBSCRIBE")) {
		conectado = 1;
	  }
  }
  mr = 0;
  //PC_SendStr(br);
  if (conectado) {
	  PC_SendStr("CONEXÃO REALIZADA COM SUCESSO");
  } else {
	  PC_SendStr("CONEXÃO FALHOU");
  }
  
  for(;;) {
	  
	  found = UTIL1_strFind(br,"MESSAGE");
	  if (found != -1 && fffvgvff) {
		  while(!found) {
			  if (br[k] == '[') {
				  found = 1;
			  }
			  k++;
		  }
		  
		  while (br[k] != ']') {
			  btopico[l] = br[k];
			  k++;
			  l++;
		  }
		  
		  btopico[l] = 0;
		  l = 0;
		  found = 0;
		  
		  while(!found) {
			  if (br[k] == '[') {
				  found = 1;
			  }
			  k++;
		  }
		  
		  while (br[k] != ']') {
			  btexto[l] = br[k];
			  k++;
			  l++;
		  }
		  btexto[l] = 0;
		  k = 0;
		  l = 0;
		  mr = 0;
		  
		  if (!UTIL1_strcmp(btopico,"EA076/grupoI2/celular")) {
			  PC_SendStr(btexto);
		  }  
	  }
	  
	  error1 = UTIL1_strcmp(br,"WIFI_DISCONNECTED");
	  error2 = UTIL1_strcmp(br,"MQTT_DISCONNECTED");
	  
	  if((!error1 || !error2) && mr == 1) {
		  PC_SendStr(br);
		  mr = 0;
	  }
	  
	  if(!PC_RecvChar(&c)){
		  while(PC_SendChar(c));
		  bt[ibt] = c;
		  ibt++;
		  if(c == 0x0D){
			  while(PC_SendChar(0x0A));
			  bt[ibt] = 0;
			  ibt = 0;
			  UTIL1_strcpy(bm,256,"PUBLISH \"EA076/grupoI2/ESP\",\"");
			  UTIL1_strcat(bm,256,bt);
			  Wifi_SendStr(bm);
			  while(!mr);
			  mr = 0;
		  }
		  
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
