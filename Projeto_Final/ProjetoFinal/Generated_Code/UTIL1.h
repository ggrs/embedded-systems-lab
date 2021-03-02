/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : UTIL1.h
**     Project     : ProjetoFinal
**     Processor   : MKL25Z128VLK4
**     Component   : Utility
**     Version     : Component 01.148, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-11-27, 08:14, # CodeGen: 0
**     Abstract    :
**          Contains various utility functions.
**     Settings    :
**          Component name                                 : UTIL1
**     Contents    :
**         strcpy  - void UTIL1_strcpy(uint8_t *dst, size_t dstSize, const unsigned char *src);
**         strcat  - void UTIL1_strcat(uint8_t *dst, size_t dstSize, const unsigned char *src);
**         strcmp  - int16_t UTIL1_strcmp(const char *, const char *);
**         strncmp - int16_t UTIL1_strncmp(const char *, const char *, size_t size);
**         strFind - int16_t UTIL1_strFind(uint8_t *str, uint8_t *subStr);
**         strlen  - uint16_t UTIL1_strlen(const char *);
**
**     * Copyright (c) 2014-2017, Erich Styger
**      * Web:         https://mcuoneclipse.com
**      * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**      * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**      * All rights reserved.
**      *
**      * Redistribution and use in source and binary forms, with or without modification,
**      * are permitted provided that the following conditions are met:
**      *
**      * - Redistributions of source code must retain the above copyright notice, this list
**      *   of conditions and the following disclaimer.
**      *
**      * - Redistributions in binary form must reproduce the above copyright notice, this
**      *   list of conditions and the following disclaimer in the documentation and/or
**      *   other materials provided with the distribution.
**      *
**      * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**      * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**      * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**      * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**      * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**      * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**      * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**      * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**      * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**      * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file UTIL1.h
** @version 01.00
** @brief
**          Contains various utility functions.
*/         
/*!
**  @addtogroup UTIL1_module UTIL1 module documentation
**  @{
*/         

#ifndef __UTIL1_H
#define __UTIL1_H

/* MODULE UTIL1. */
#include "MCUC1.h" /* SDK and API used */
#include "UTIL1config.h" /* configuration */

/* other includes needed */
#include <string.h>
#include <stddef.h> /* for size_t */


typedef enum {
  UTIL1_SEP_NUM_TYPE_UINT8, /* uint8_t number type */
  UTIL1_SEP_NUM_TYPE_UINT8_HEX_NO_PREFIX /* uint8_t hex number type, no 0x prefix */
} UTIL1_SeparatedNumberType;

#ifdef __cplusplus
extern "C" {
#endif

void UTIL1_strcpy(uint8_t *dst, size_t dstSize, const unsigned char *src);
/*
** ===================================================================
**     Method      :  UTIL1_strcpy (component Utility)
**     Description :
**         Same as normal strcpy, but safe as it does not write beyond
**         the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * dst             - Pointer to destination string
**         dstSize         - Size of the destination buffer (in
**                           bytes).
**       * src             - Pointer to source string.
**     Returns     : Nothing
** ===================================================================
*/

void UTIL1_strcat(uint8_t *dst, size_t dstSize, const unsigned char *src);
/*
** ===================================================================
**     Method      :  UTIL1_strcat (component Utility)
**     Description :
**         Same as normal strcat, but safe as it does not write beyond
**         the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * dst             - Pointer to destination string
**         dstSize         - Size of the destination buffer (in
**                           bytes).
**       * src             - Pointer to source string.
**     Returns     : Nothing
** ===================================================================
*/

#define UTIL1_strcmp(str1, str2) \
  strcmp(str1, str2)

/*
** ===================================================================
**     Method      :  UTIL1_strcmp (component Utility)
**     Description :
**         Wrapper to the standard strcmp() routine
**     Parameters  :
**         NAME            - DESCRIPTION
**       * str1            - Pointer to string
**       * str2            - Pointer to string
**     Returns     :
**         ---             - Returns zero if the two strings are the
**                           same
** ===================================================================
*/

#define UTIL1_strncmp(str1, str2, size) \
  strncmp(str1, str2, size)

/*
** ===================================================================
**     Method      :  UTIL1_strncmp (component Utility)
**     Description :
**         Wrapper to the standard strncmp() routine
**     Parameters  :
**         NAME            - DESCRIPTION
**       * str1            - Pointer to string
**       * str2            - Pointer to string
**         size            - 
**     Returns     :
**         ---             - Returns zero if the two strings are the
**                           same
** ===================================================================
*/

#define UTIL1_strlen(str) \
  strlen(str)

/*
** ===================================================================
**     Method      :  UTIL1_strlen (component Utility)
**     Description :
**         Wrapper to the standard strlen() function.
**     Parameters  :
**         NAME            - DESCRIPTION
**         str             - 
**     Returns     :
**         ---             - size of strinig
** ===================================================================
*/

int16_t UTIL1_strFind(uint8_t *str, uint8_t *subStr);
/*
** ===================================================================
**     Method      :  UTIL1_strFind (component Utility)
**     Description :
**         Searches a substring inside a string and returns the
**         position.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * str             - Pointer to string which will be searched
**       * subStr          - Pointer to substring to search
**                           inside str
**     Returns     :
**         ---             - -1 if not found, otherwise the character
**                           index.
** ===================================================================
*/

/* END UTIL1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __UTIL1_H */
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
