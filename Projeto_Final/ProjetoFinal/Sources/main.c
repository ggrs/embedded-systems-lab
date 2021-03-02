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
#include "LT.h"
#include "BitIoLdd7.h"
#include "WAIT2.h"
#include "Timer.h"
#include "RealTimeLdd1.h"
#include "TU3.h"
#include "EE241.h"
#include "GI2C1.h"
#include "CI2C1.h"
#include "Timer_Buzzer.h"
#include "RealTimeLdd2.h"
#include "TU4.h"
#include "PIR.h"
#include "ExtIntLdd4.h"
#include "Buzzer.h"
#include "BitIoLdd8.h"
#include "CS1.h"
#include "TU6.h"
#include "PIR2.h"
#include "BitIoLdd9.h"
#include "WAIT1.h"
#include "SM1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "RTC1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
volatile uint8_t br[256]; 				//!< Buffer que armazena caracteres recebidos pelo ESP.
volatile uint8_t ibr = 0;				//!< Indice do buffer br.
volatile uint8_t mr = 0; 				//!< Variavel booleana que diz se uma mensagem foi recebida.
volatile uint8_t time_counter = 2;		//!< Define o intervalo de 2 segundos.
volatile uint8_t rtc_ready = 0;			//!< Define que se passaram 2 segundos.
uint8_t conectado;						//!< Espera confirmaÃ§Ã£o que houve conexÃ£o correta com o wi-fi.
uint8_t membuf[16];						//!< Buffer para transferencia para a memoria
LDD_RTC_TTime time;						//!< Struct de armazenamento de data e hora
volatile uint8_t move = 0;				//!< Variavel que indica movimento por interrupcao



/** Converte data e hora da struct time em string.
 * Entrada: string de destino.
 */
void Time_2str(uint8_t *s){
	
	RTC1_GetTime(RTC1_DeviceData, &time); 
	
	
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


/** Funcao que pega a data e a transforma em uma string.
 * 	Entrada: string de destino.
 */
void Date_2str(uint8_t *s){
	
	RTC1_GetTime(RTC1_DeviceData, &time); 
	
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
	*s = 0;
}

/** Funcao que pega a hora e a transforma em uma string.
 * 	Entrada: string de destino.
 */
void Hour_2str(uint8_t *s){

	RTC1_GetTime(RTC1_DeviceData, &time);
	
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

/** Funcao que envia string para o terminal.
 * 	Entrada: string a ser enviada.
 */
void PC_SendStr(uint8_t *s) {
	
	while(*s) {
		while(PC_SendChar(*s));
		s++;
	}
	while(PC_SendChar(0x0D));
	while(PC_SendChar(0x0A));
}

/** Funcao que envia string para o modulo ESP.
 * 	Entrada: string a ser enviada.
 */
void Wifi_SendStr(uint8_t *s) {
	
	while(*s) {
		while(Wifi_SendChar(*s));
		s++;
	}
	while(Wifi_SendChar(0x0D));
	while(Wifi_SendChar(0x0A));
}

/** Funcao para se inscrever em um topico.
 * 	Entrada: string que contem topico.
 */
void Sub_topic(uint8_t *s){
	
	conectado = 0;	
	  while (!conectado) {	
		 Wifi_SendStr(s);
		 while(!mr);
		 if(!(UTIL1_strcmp(br,"OK SUBSCRIBE"))) {
			conectado = 1;
		 }
	  }
	  mr = 0;
	  
}


int main(void)

/*lint -restore Enable MISRA rule (6.3) checking. */
{
	
  /* Write your local variable definition here */
	
	// Variáveis para Projeto Final:
	uint16_t timer_buz = 0; 
	uint8_t alert = 1; 
	uint16_t pos_mem = 0x00;
	uint8_t mem_read[21];		// Buffer de leitura de uma temperatura da EEPROM
	uint16_t iread = 0;			// Indici de leitura da posicao de memoria
	
	// Variaveis de Inicializacao Buffer de Mensagem.
	
	uint8_t bm[256]; 	// Buffer que armazena as mensagens enviadas ao ESP e ao terminal.
	
	// Variaveis de Comunicacao ESP, TERMINAL, CELULAR.

	uint8_t btopico[256], btexto[256];	// Buffers de topico e texto.
	int8_t found = 0;					// Auxiliar.
	uint8_t k = 0;						// Auxiliar.
	uint8_t l = 0;						// Auxiliar.
	uint8_t bl[21];						// Buffer que contém data e hora a serem exibido no terminal.
	uint8_t bhour[9];					// Buffer que armazena a hora
	uint8_t bdate[11];					// Buffer que armazena a data
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* ----------------------------- Write your code here --------------------------------- */
  
  // Inicializo o RTC e coloco o sentido de rotacao Vent como default.
  RTC1_Enable(RTC1_DeviceData);
  
  
  // 1) Connect Wifi
  UTIL1_strcpy(bm,256,"CONNWIFI \"EA076R\",\"FRDMKL25\"");
  
  while (!conectado) {
	  Wifi_SendStr(bm);
	  while(!mr);
	  if(!UTIL1_strcmp(br,"CONNECT WIFI")) {
		  conectado = 1;
	  }
  }
  mr = 0;
  
  // 2) Get MAC
  UTIL1_strcpy(bm,256,"GETMAC");
  
  Wifi_SendStr(bm);
  while (!mr);
  mr = 0;
  
  // 3) Connect MQTT
  UTIL1_strcpy(bm,256,"CONNMQTT \"192.168.1.111\",1883,\"");
  UTIL1_strcat(bm,256,br);
  UTIL1_strcat(bm,256,"\",\"aluno\",\"UNICAMP\"");
  conectado = 0;
	
  while (!conectado) {
	  Wifi_SendStr(bm);
	  while(!mr);
	  if(!UTIL1_strcmp(br,"CONNECT MQTT")) {
		  conectado = 1;
	  }
  }
  mr = 0;
  
  if (conectado) {
  	  PC_SendStr("CONEXÃO REALIZADA COM SUCESSO");
  } else {
  	  PC_SendStr("CONEXÃO FALHOU");
  }
  
  // 4) Subscribe
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/move\"");
  Sub_topic(bm);  
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/log\"");
  Sub_topic(bm); 
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/command\"");
  Sub_topic(bm);
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/alarm\"");
  Sub_topic(bm);
  
  for(;;){
	  
	  Timer_Buzzer_GetTimeMS(&timer_buz);
	  if(timer_buz >= 500){
		  Buzzer_ClrVal();
	  }
	  if(move == 1){
		  PC_SendStr("movimento");		
		  
		  // Colocar data e hora na EEPROM
		  Time_2str(bl);
		  EE241_WriteBlock(pos_mem, bl, 21);
		  pos_mem = pos_mem + 0x15;
		  
		  
		  // Envio notificacao ao celular com data e hora do movimento
		  Date_2str(bdate);
		  Hour_2str(bhour);
		  UTIL1_strcpy(bm,256,"PUBLISH \"EA076/grupoI2/move\",\"");
		  UTIL1_strcat(bm,256,bdate);
		  UTIL1_strcat(bm,256," ");
		  UTIL1_strcat(bm,256,bhour);
		  UTIL1_strcat(bm,256,"\"");
		  Wifi_SendStr(bm);
		  
		  // Verifico alarme
		  if(alert == 1){
			  Buzzer_SetVal();
			  Timer_Buzzer_Reset();
		  } else if(alert == 0){
			  Buzzer_ClrVal();
		  }
		  
		  move = 0;
	  }
	  
	  found = UTIL1_strFind(br,"MESSAGE");
	  if (found != -1 && mr == 1) {
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
		  
		  if(!(UTIL1_strcmp(btopico, "EA076/grupoI2/alarm"))){
			  if(!(UTIL1_strFind(btexto, "ON"))){
				  alert = 1;
			  } else if(!(UTIL1_strFind(btexto, "OFF"))){
				  alert = 0;
				  Buzzer_ClrVal();
			  }
		  }
	  
		  if(!(UTIL1_strcmp(btopico, "EA076/grupoI2/command"))){
			  if(!(UTIL1_strFind(btexto, "Dump"))){
				  PC_SendStr("DUMP");
				  iread = 0x00;
				  while(iread < pos_mem){
					  EE241_ReadBlock(iread, mem_read, 21);
					  iread = iread + 0x15;
					  // Mando para o topico log
					  UTIL1_strcpy(bm,256,"PUBLISH \"EA076/grupoI2/log\",\"");
					  UTIL1_strcat(bm,256,mem_read);
					  UTIL1_strcat(bm,256,"\"");
					  Wifi_SendStr(bm);				  
				  }
				  pos_mem = 0x00;
			  } 
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
