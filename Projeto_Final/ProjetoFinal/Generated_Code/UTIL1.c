/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : UTIL1.c
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
** @file UTIL1.c
** @version 01.00
** @brief
**          Contains various utility functions.
*/         
/*!
**  @addtogroup UTIL1_module UTIL1 module documentation
**  @{
*/         

/* MODULE UTIL1. */

#include "UTIL1.h"

/* Internal method prototypes */
static void ShiftRightAndFill(uint8_t *dst, uint8_t fill, uint8_t nofFill);

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
/*!
  \brief copy the string src into dst. It performs the same task as strncpy, except
     - always terminates the result string.
     - does not zero out the remaining part in dst.
     Note: dstSize is the size of dst INCLUDING zero byte.
     Precondition: src, dst != NULL
  \param[in,out] dst Start of string buffer, where to append the number string
  \param[in] dstSize The size of the buffer, including the zero byte
  \param[in] src The source string to copy
*/
void UTIL1_strcpy(uint8_t *dst, size_t dstSize, const unsigned char *src)
{
  dstSize--; /* for zero byte */
  while (dstSize > 0 && *src != '\0') {
    *dst++ = *src++;
    dstSize--;
  }
  *dst = '\0';
}

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
/*!
  \brief Concat the string src into dst. Always terminates the result string.
     Note: count is the size of dst INCLUDING zero byte.
     Precondition: src, dst != NULL
  \param[in,out] dst Start of string buffer, where to append the number string
  \param[in] dstSize The size of the buffer, including the zero byte
  \param[in] src The source string to add
  */
void UTIL1_strcat(uint8_t *dst, size_t dstSize, const unsigned char *src)
{
  dstSize--; /* for zero byte */
  /* point to the end of the source */
  while (dstSize > 0 && *dst != '\0') {
    dst++;
    dstSize--;
  }
  /* copy the src in the destination */
  while (dstSize > 0 && *src != '\0') {
    *dst++ = *src++;
    dstSize--;
  }
  /* terminate the string */
  *dst = '\0';
}

/*
** ===================================================================
**     Method      :  ShiftRightAndFill (component Utility)
**
**     Description :
**         Moves the content of a string to the right and fills the space 
**         on the left side with a pattern
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void ShiftRightAndFill(uint8_t *dst, uint8_t fill, uint8_t nofFill)
{
  signed char i, j;

  j = 0;
  while(dst[j] != '\0') {
    j++;
  }
  i = (signed char)nofFill;
  if (i==j) {
    /* nothing to do, we are done */
  } else if (i>j) {
    while (j>=0) {
      dst[i] = dst[j];
      i--; j--;
    }
    while(i>=0) {
      dst[i] = fill;
      i--;
    }
  } else {
    /* hmmm, not enough space, return what we have, do nothing */
  }
}

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
/***
int16_t UTIL1_strcmp(const char *, const char *)
{
  Method is implemented as macro in the header file as wrapper to the standard strcmp() function
}
*/

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
/***
int16_t UTIL1_strncmp(const char *, const char *, size_t size)
{
  /Method is implemented as macro in the header file as wrapper to the standard strncmp() function
}
*/

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
/***
uint16_t UTIL1_strlen(const char *)
{
  Method is implemented as macro in the header file as wrapper to the standard strlen() function
}
*/

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
int16_t UTIL1_strFind(uint8_t *str, uint8_t *subStr)
{
  int16_t i, len;

  len = (int16_t)UTIL1_strlen((char*)subStr);
  for (i=0; *str!='\0'; i++, str++) {
    if (UTIL1_strncmp((char*)str, (char*)subStr, len)==0) {
      return i; /* found */
    }
  }
  return -1; /* not found */
}

/* END UTIL1. */

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
