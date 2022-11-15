/*! @file : lpuaro.h
 * @author  Nestor Gamarra Barbosa
 * @version 1.0.0
 * @date    11 nov 2022
 * @brief   Driver para 
 * @details
 *
 */

#ifndef LIBRERIA_IOT_LPUART0_H_
#define LIBRERIA_IOT_LPUART0_H_
/***************************
 * Includes
 **************************/
#include "fsl_common.h"
#include "fsl_lpuart.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
/*********
 * Definitions
 **********/


/*********
 * Private Prototypes
 **********/


/*********
 * External vars
 **********/


/*********
 * Local vars
 **********/


/*********
 * Private Source Code
 **********/


/*********
 * Public Source Code
 **********/
uint8_t leer_dato(void);
uint8_t leer_bandera_nuevo_dato(void);
void  escribir_bandera_nuevo_dato(uint8_t nuevo_valor);
uint8_t lpuart0_leer_dato(void);
uint8_t lpuart0_leer_bandera_nuevo_dato(void);
void lpuart0_escribir_bandera_nuevo_dato(uint8_t nuevo_valor);
void lpuart0_borrar_buffer(void);
/** @} */ // end of X group
/** @} */ // end of X group

#endif
