/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : EE241.h
**     Project     : ProjetoFinal
**     Processor   : MKL25Z128VLK4
**     Component   : 24AA_EEPROM
**     Version     : Component 01.032, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-11-27, 08:14, # CodeGen: 0
**     Abstract    :
**         Driver for Microchip 24_AA/LC EEPROMs
**     Settings    :
**          Component name                                 : EE241
**          Device                                         : 8
**          Initial Device Address                         : 0
**          Block buffer size                              : 12
**          Acknowledge Polling                            : Enabled
**            Page Write Time (ms)                         : 10
**            Wait                                         : WAIT1
**          Connection                                     : 
**            I2C                                          : GI2C1
**            Write Protection Pin                         : Disabled
**          Timeout                                        : Disabled
**          Shell                                          : Disabled
**     Contents    :
**         ReadByte   - byte EE241_ReadByte(EE241_Address addr, byte *data);
**         WriteByte  - byte EE241_WriteByte(EE241_Address addr, byte data);
**         ReadBlock  - byte EE241_ReadBlock(EE241_Address addr, byte *data, word dataSize);
**         WriteBlock - byte EE241_WriteBlock(EE241_Address addr, byte *data, word dataSize);
**
**     License   :  Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2013, all rights reserved.
**     This an open source software implementation with Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file EE241.h
** @version 01.00
** @brief
**         Driver for Microchip 24_AA/LC EEPROMs
*/         
/*!
**  @addtogroup EE241_module EE241 module documentation
**  @{
*/         

#ifndef __EE241_H
#define __EE241_H

/* MODULE EE241. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited components */
#include "WAIT1.h"
#include "GI2C1.h"

#include "Cpu.h"

/* supported device ID's */
#define EE241_DEVICE_ID_8       8 /* 24AA08, 24LC08 */
#define EE241_DEVICE_ID_16     16 /* 24AA16, 24LC16 */
#define EE241_DEVICE_ID_32     32 /* 24AA32, 24LC32 */
#define EE241_DEVICE_ID_256   256 /* 24AA256, 24LC256, 24FC256 */
#define EE241_DEVICE_ID_512   512 /* 24AA512, 24LC512, 24FC256 */
#define EE241_DEVICE_ID_1025 1025 /* 24AA1025, 24LC1025, 24FC1025 */
/* actual device */
#define EE241_DEVICE_ID      EE241_DEVICE_ID_8

#define EE241_BLOCK_BUF_SIZE 12         /* buffer used for block read/write. Max is 128. Keep it small to reduce stack consumption. */

#if EE241_DEVICE_ID==EE241_DEVICE_ID_8
  #define EE241_MAX_I2C_ADDR_MASK 0     /* A2|A1|A0 are not used */
  #define EE241_MAX_ADDRESS       0x03FF /* 8 kBit is 1KByte */
  #define EE241_ADDRT             word  /* a word/16bit is enough to hold the address */
  #define EE241_PAGE_SIZE         16    /* maximum page size (for page/block operation) */
#elif EE241_DEVICE_ID==EE241_DEVICE_ID_16
  #define EE241_MAX_I2C_ADDR_MASK 0     /* A2|A1|A0 are not used */
  #define EE241_MAX_ADDRESS       0x07FF /* 16 kBit is 2KByte */
  #define EE241_ADDRT             word  /* a word/16bit is enough to hold the address */
  #define EE241_PAGE_SIZE         16    /* maximum page size (for page/block operation) */
#elif EE241_DEVICE_ID==EE241_DEVICE_ID_32
  #define EE241_MAX_I2C_ADDR_MASK 7     /* A2|A1|A0 form the I2C device address => address cannot be more than 7 (8 devices) */
  #define EE241_MAX_ADDRESS       0x0FFF /* 32 kBit are 4KByte */
  #define EE241_ADDRT             word  /* a word/16bit is enough to hold the address */
  #define EE241_PAGE_SIZE         8     /* maximum page size (for page/block operation) */
#elif EE241_DEVICE_ID==EE241_DEVICE_ID_256
  #define EE241_MAX_I2C_ADDR_MASK 7     /* A2|A1|A0 form the I2C device address => address cannot be more than 7 (8 devices) */
  #define EE241_MAX_ADDRESS       0x7FFF /* 256 kBit are 32KByte */
  #define EE241_ADDRT             word  /* a word/16bit is enough to hold the address */
  #define EE241_PAGE_SIZE         64    /* maximum page size (for page/block operation) */
#elif EE241_DEVICE_ID==EE241_DEVICE_ID_512
  #define EE241_MAX_I2C_ADDR_MASK 7     /* A2|A1|A0 form the I2C device address => address cannot be more than 7 (8 devices) */
  #define EE241_MAX_ADDRESS       0xFFFF /* 512 kBit are 64KByte */
  #define EE241_ADDRT             word  /* a word/16bit is enough to hold the address */
  #define EE241_PAGE_SIZE         128   /* maximum page size (for page/block operation) */
#elif EE241_DEVICE_ID==EE241_DEVICE_ID_1025
  #define EE241_MAX_I2C_ADDR_MASK 3     /* A1|A0 form the I2C device address => address cannot be more than 3 (4 devices) */
  #define EE241_MAX_ADDRESS       0x1FFFF /* 1024 kBit are 128KByte */
  #define EE241_ADDRT             dword /* a longword/32bit is needed to hold the address */
  #define EE241_PAGE_SIZE         128   /* maximum page size (for page/block operation) */
#else
  #error "unknown device?"
#endif

#define EE241_DO_ACKNOWLEDGE_POLLING    1 /* Perform acknowledge polling in the driver */
#define EE241_PAGE_WRITE_TIME_MS        10 /* Page Write Time as per data sheet */
#define EE241_ACK_POLLING_TIME_US       100 /* Acknowledge polling time in the I2C driver*/

#ifndef __BWUserType_EE241_Address
#define __BWUserType_EE241_Address
  typedef  EE241_ADDRT EE241_Address;  /* A type large enought to hold the address, depending on the EEPROM used. */
#endif

#define EE241_PARSE_COMMAND_ENABLED  0 /* set to 1 if method ParseCommand() is present, 0 otherwise */

byte EE241_WriteByte(EE241_Address addr, byte data);
/*
** ===================================================================
**     Method      :  EE241_WriteByte (component 24AA_EEPROM)
**     Description :
**         Writes a single byte to specified address
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - The address inside the EEPROM
**         data            - The data value to write
**     Returns     :
**         ---             - Error code, possible values
**                           ERR_OK - OK
**                           otherwise it can return an error code of
**                           the underlying communication protocol.
** ===================================================================
*/

byte EE241_ReadByte(EE241_Address addr, byte *data);
/*
** ===================================================================
**     Method      :  EE241_ReadByte (component 24AA_EEPROM)
**     Description :
**         Reads a single byte from the given memory address
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - The address where to read from memory.
**       * data            - Pointer to a location where to store the
**                           data
**     Returns     :
**         ---             - Error code, possible values
**                           ERR_OK - OK
**                           otherwise it can return an error code of
**                           the underlying communication protocol.
** ===================================================================
*/

byte EE241_ReadBlock(EE241_Address addr, byte *data, word dataSize);
/*
** ===================================================================
**     Method      :  EE241_ReadBlock (component 24AA_EEPROM)
**     Description :
**         Read a block of memory.
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - Address where to read the memory
**       * data            - Pointer to a buffer where to store the
**                           data
**         dataSize        - Size of buffer the data pointer
**                           is pointing to
**     Returns     :
**         ---             - Error code, possible values
**                           ERR_OK - OK
**                           otherwise it can return an error code of
**                           the underlying communication protocol.
** ===================================================================
*/

byte EE241_WriteBlock(EE241_Address addr, byte *data, word dataSize);
/*
** ===================================================================
**     Method      :  EE241_WriteBlock (component 24AA_EEPROM)
**     Description :
**         Writes a block of data to the EEPROM
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - Address of memory
**       * data            - Pointer to the data
**         dataSize        - Size of data
**     Returns     :
**         ---             - Error code, possible values
**                           ERR_OK - OK
**                           ERR_OVERFLOW - data block passed has either
**                           size of zero or exceeds internal buffer
**                           size
**                           otherwise it can return an error code of
**                           the underlying communication protocol.
** ===================================================================
*/

byte EE241_WriteBlockPage(EE241_Address addr, byte *data, word dataSize);
/*
** ===================================================================
**     Method      :  EE241_WriteBlockPage (component 24AA_EEPROM)
**
**     Description :
**         Writes a block with pages of data to the EEPROM
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END EE241. */

#endif
/* ifndef __EE241_H */
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