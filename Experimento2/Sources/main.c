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

volatile uint8_t br[256]; 				//!< Buffer que armazena caracteres recebidos pelo ESP.
volatile uint8_t ibr = 0;				//!< Indice do buffer br.
volatile uint8_t mr = 0; 				//!< Variavel booleana que diz se uma mensagem foi recebida.
volatile uint8_t time_counter = 2;		//!< Define o intervalo de 2 segundos.
volatile uint8_t rtc_ready = 0;			//!< Define que se passaram 2 segundos.
uint8_t conectado;						//!< Espera confirmação que houve conexão correta com o wi-fi.
LDD_RTC_TTime time;						//!< Struct de armazenamento de data e hora

/** Função que determina o duty cicle do motor a partir de um valor de porcentagem inserido.
 * 	Entrada: valor (dc) de 0-100. 
 */
void SetDC(uint8_t dc) {
	uint16_t n;		// Variável que fornecerá o valor PWM para o motor
	
	if (dc > 100) dc = 100;
	n = (100 - dc)*655;
	
	PWM1_SetRatio16(n);
}

/** Converte valor em decimal de temperatura para uma string de temperatura.
 *  Entradas: Valor de temperatura em décimo de grau (te) e string de destino (*s).
 */ 
void Temp_2str(uint16_t te, uint8_t *s){ 

	uint8_t c, d, u;   // centena, dezena, unidade 

	c= te/100; 
	te = te%100; 
	d= te/10; 
	u= te%10; 
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

/** Função que envia string para o terminal.
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

/** Função que envia string para o módulo ESP.
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

/** Função para se inscrever em um tópico.
 * 	Entrada: string que contém tópico.
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
	
	// Variaveis de Inicialização Buffer de Mensagem.
	
	uint8_t bm[256]; 	// Buffer que armazena as mensagens enviadas ao ESP e ao terminal.
	
	// Variaveis de Inicializacao Temperatura.
	uint8_t btemp[5];	// String que contém temperatura.
	uint16_t n; 		// Auxiliar para conversão de temperatura.
	uint16_t mv;		// Auxiliar para conversão de temperatura.
	int16_t tdc; 		// Temperatura em decimo de grau.
	int16_t limiar = 0; // Armazena o valor do limiar de temperatura.
	
	// Variaveis do Motor DC/PWM.
	uint8_t t; 			// Auxiliar para definir dc.
	int8_t i = 0;		// Auxiliar para definir dc.
	uint8_t dc = 0; 	// Valor do duty-cicle.
	int8_t ligado = 0; 	// Armazena o estado do motor: 0=desligado, 1=ligado, 2=automatico.

	// Variaveis de Comunicacao ESP, TERMINAL, CELULAR.

	uint8_t btopico[256], btexto[256];	// Buffers de tópico e texto.
	int8_t found = 0;					// Auxiliar.
	int8_t found2 = 0;					// Auxiliar.
	uint8_t k = 0;						// Auxiliar.
	uint8_t l = 0;						// Auxiliar.
	uint8_t bl[25];						// Buffer que contém data e hora a serem exibido no terminal.
	uint32_t data = 0; 					// Auxilia na conversão dos valores de data e hora do RTC.
	
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* ----------------------------- Write your code here --------------------------------- */
  
  // Inicializo o RTC e coloco o sentido de rotação Vent como default.
  RTC1_Enable(RTC1_DeviceData);
  PTE29_SetVal();	
  PTE30_ClrVal();
  
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
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/dir\"");
  Sub_topic(bm);  
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/power\"");
  Sub_topic(bm); 
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/mode\"");
  Sub_topic(bm); 
  UTIL1_strcpy(bm,256,"SUBSCRIBE \"EA076/grupoI2/config\"");
  Sub_topic(bm); 
  
  for(;;){
	  
	  /* Enviar temperatura a cada 2 segundos para o celular. Também envia data e hora no terminal.
	   * 
	   */
	  if(rtc_ready){
		  
		  (void)AD1_Measure(TRUE); 		// Faz a conversão da temperatura e espera o resultado.
		  (void)AD1_GetValue16(&n); 	// Coloca o resultado na variável n.
		  mv = (3300 * n) / 65535;		// Converto valor em bits para mV.
		  tdc = mv - 600; 				// Converto mV para decimo de grau.	
		  Temp_2str(tdc, btemp);		// Montar string de temperatura.
		  
		  /* Monto string de envio e publico no tópico.
		   * 
		   */
		  UTIL1_strcpy(bm,256,"PUBLISH \"EA076/grupoI2/temp\",\"");
		  UTIL1_strcat(bm,256,btemp);
		  UTIL1_strcat(bm,256,"\"");
		  Wifi_SendStr(bm);
		 
		  rtc_ready = 0; 	// Reset do rtc_ready preparando para esperar mais 2 segundos.
		  
		  Time_2str(bl);
		  PC_SendStr(bl);	// Envio string com data e hora para o terminal.
	  }
	  
	  /* Recebo a mensagem e separo tópico e conteúdo.
	   * 
	   */
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
		  
		  /* Caso tópico seja "dir" defino o sentido de rotação.
		   * 
		   */
		  if(!(UTIL1_strcmp(btopico, "EA076/grupoI2/dir"))){
			  if(!(UTIL1_strcmp(btexto, "Vent"))){
				  PTE29_SetVal();
				  PTE30_ClrVal();
			  } else if(!(UTIL1_strcmp(btexto, "Exaust"))){
				  PTE29_ClrVal();
				  PTE30_SetVal();
			  }
		  }
		  /* Caso o tópico seja "power" defino o valor do duty-cicle.
		   * 
		   */
		  if(!(UTIL1_strcmp(btopico, "EA076/grupoI2/power"))){
			  dc = 0;
			  i = 0;
			  while(btexto[i] != 0){
				  t = btexto[i];
				  dc = dc * 10;
				  dc = dc + (t - 0x30);
				  i++;
			  }
		  }
		  /* Caso o tópico seja "mode" configuro motor para On, Off ou Auto.
		   * 
		   */
		  if(!(UTIL1_strcmp(btopico, "EA076/grupoI2/mode"))){
			  if(!(UTIL1_strcmp(btexto, "On"))){
				  ligado = 1;
			  }
			  if(!(UTIL1_strcmp(btexto, "Off"))){
				  ligado = 0;
			  }
			  if(!(UTIL1_strcmp(btexto, "Auto"))){
				  ligado = 2;			  
			  }
			  
			  
		  } 
		  /* Caso seja o topico seja "config" defino nova data, hora ou limiar de temperatura.
		   *  
		   */
		  if(!(UTIL1_strcmp(btopico, "EA076/grupoI2/config"))){
			  
			  found2 = 0;
			  
			  if(!(UTIL1_strFind(btexto, "DATE"))){			
				  
				  while(!found2){
					  if (btexto[k] == '/') {
						  
						  data = 0;
						  data = data + ((btexto[k-2] - 0x30) * 10); 
						  data = data + ((btexto[k-1] - 0x30));
						  time.Day = data;
						  data = 0;
						  data = data + ((btexto[k+1] - 0x30) * 10); 
						  data = data + ((btexto[k+2] - 0x30));
						  time.Month = data;
						  data = 0;
						  data = data + ((btexto[k+4] - 0x30) * 1000); 
						  data = data + ((btexto[k+5] - 0x30) * 100); 
						  data = data + ((btexto[k+6] - 0x30) * 10); 
						  data = data + ((btexto[k+7] - 0x30));
						  time.Year = data;
						  
						  RTC1_SetTime(RTC1_DeviceData, &time);
			
						  found2 = 1;
					  }
					  k++;
				  }
			  } else if(!(UTIL1_strFind(btexto, "TIME"))){		
				  while(!found2){
					  if (btexto[k] == ':') {
						  
						  data = 0;
						  data = data + ((btexto[k-2] - 0x30) * 10); 
						  data = data + ((btexto[k-1] - 0x30));
						  time.Hour = data;
						  data = 0;
						  data = data + ((btexto[k+1] - 0x30) * 10); 
						  data = data + ((btexto[k+2] - 0x30));
						  time.Minute = data;
						  data = 0;
						  data = data + ((btexto[k+4] - 0x30) * 10); 
						  data = data + ((btexto[k+5] - 0x30));
						  time.Second = data;
	
						  RTC1_SetTime(RTC1_DeviceData, &time);
						  
						  found2 = 1;
					  }
					  k++;
				  }
			  } else if(!(UTIL1_strFind(btexto, "TEMP"))){	
				  while(!found2){
					  
					  if (btexto[k] == '.') {
						  PC_SendStr(btexto);
						  limiar = 0;
						  limiar = limiar + ((btexto[k-2] - 0x30) * 100);
						  limiar = limiar + ((btexto[k-1] - 0x30) * 10);
						  limiar = limiar + ((btexto[k+1] - 0x30));
						  
						  found2 = 1;
					  }				  
					  k++;
				  }
			  }
			 
			  k = 0;
			  
			  }  
	  }   
	  /* Aciono o motor de acordo com o duty-cicle e o estado dele.
	   * 
	   */
	  if(ligado == 1){
		  SetDC(dc);
	  } else if(ligado == 0){
		  SetDC(0);
	  } else if(ligado == 2){
		  if(tdc >= limiar){
			  SetDC(dc);
		  } else {
			  SetDC(0);
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
