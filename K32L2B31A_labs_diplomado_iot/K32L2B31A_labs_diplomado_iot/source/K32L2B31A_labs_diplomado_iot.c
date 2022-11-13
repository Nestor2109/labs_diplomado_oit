/*
 * @file    K32L2B31A_labs_diplomado_iot
 * @author Nestor Gamarra
 * @version 0.02
 * @date 05/10/2022
 * @brief   Funcion principal main.
 * @details
  			v0.00 proyecto base
 */
/* TODO: insert other include files here. */


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"


/// fls ////////////////////
#include "fsl_debug_console.h"
#include "fsl_adc16.h"


//// personales ///////////////

#include "lpuart0.h"


/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 *
 *
 *
 */

#define ADC16_BASE          ADC0
#define ADC16_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL  3U

#define BOARD_LED_GPIO1     BOARD_LED_GREEN_GPIO
#define BOARD_LED_GPIO_PIN1 BOARD_LED_GREEN_GPIO_PIN

#define BOARD_LED_GPIO2     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN2 BOARD_LED_RED_GPIO_PIN


volatile uint32_t g_systickCounter;


///////////////////// funciones ////////////////////////
///////////////////////////////////////////////////////

void led_encendidos();

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

////////////////// definition /////////////////////////////7

typedef struct _iot_nodo_data{
	uint32_t preamble;
	uint16_t frame_sync;
	//------------------------------------
	uint32_t end_divice_ID;
	uint16_t payload;
	uint16_t auth;
	//------------------------------------
	uint16_t FCS;
	//------------------------------------
} iot_nodo_data_t;

/***************************
 * Private Source Code
 **************************/
void ec25_print_data_raw(uint8_t *data_ptr, uint32_t data_size) {
	for (uint32_t i = 0; i < data_size; i++) {
		PRINTF("%02x   ", *(data_ptr + i));
	}
}

void ec25_print_data_ascii_hex(uint8_t *data_ptr, uint32_t data_size) {
	for (uint32_t i = 0; i < data_size; i++) {
		PRINTF("0x%02x ", *(data_ptr + i));
	}
}


int main(void) {

uint8_t	aux_recepcion = "H";

iot_nodo_data_t datos_locales;

datos_locales.preamble=9;
datos_locales.frame_sync=2;
datos_locales.end_divice_ID=3;
datos_locales.payload=4;
datos_locales.auth=3;
datos_locales.FCS=7;



    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitLEDsPins();


#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();


#endif



    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    while(1) {
    	if(leer_bandera_nuevo_dato()!=0){
    	escribir_bandera_nuevo_dato(0);

    	if (aux_recepcion == 83){
    		ec25_print_data_raw((uint8_t *)(&datos_locales),sizeof(datos_locales));
    	}


    	aux_recepcion = leer_dato();
    	PRINTF("%c\r\n",aux_recepcion);

    	if (aux_recepcion == 71){
    		led_on_green(); //Prender el LED
    	}

    	if (aux_recepcion == 103){
    		led_off_green(); //Apagar el LED
    	}


    	if (aux_recepcion == 82){
    		led_on_red();
    	}

    	if (aux_recepcion == 114){
    		led_off_red();
    	}

    	if(aux_recepcion == 76){
    		ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP, &ADC0_channelsConfig[0]);

    		    	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP)))
    		    	    	                	            {
    		    	    	                	            }
    		    	PRINTF("ADC Value: %d", ADC16_GetChannelConversionValue(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP));
    	}



       }



        __asm volatile ("nop");
    }

    while (2) {
    		if(leer_bandera_nuevo_dato()!=0){
    			escribir_bandera_nuevo_dato(0);
    			if (aux_recepcion == 83){

    				ec25_print_data_raw((uint8_t *)(&datos_locales),sizeof(datos_locales));
    			}
    		}
    		/* 'Dummy' NOP to allow source level single stepping of
    		 tight while() loop */
    		__asm volatile ("nop");
    	}
    return 0 ;
}


void led_encendidos(){


}












//////////////////////////////////////////////////////////////////////////////////********************************************/////////////////////////////////////////////////////////////////////////



















/*
//volatile static uint8_t i = 0 ;
//float Vout;
//float LUX ;
//float Iout;
uint8_t dato_lpuart0;
/* LPUART0_IRQn interrupt handler */
/*void LPUART0_SERIAL_RX_TX_IRQHANDLER(void) {
  uint32_t intStatus;*/
  /* Reading all interrupt flags of status registers */
  /*intStatus = LPUART_GetStatusFlags(LPUART0_PERIPHERAL); */
  /* Flags can be cleared by reading the status register and reading/writing data registers.
    See the reference manual for details of each flag.
    The LPUART_ClearStatusFlags() function can be also used for clearing of flags in case the content of data/FIFO regsiter is not used.
    For example:
        status_t status;
        status = LPUART_ClearStatusFlags(LPUART0_PERIPHERAL, intStatus);
  */

  /* Place your code here

  if ((kLPUART_RxDataRegFullFlag) & intStatus) {

  dato_lpuart0 = LPUART_ReadByte(LPUART0);

  }*/

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
 /* #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

void SysTick_Handler(void){
if (g_systickCounter != 0U){
    g_systickCounter--;

    }
    }

void SysTick_DelayTicks(uint32_t n)
    {
       g_systickCounter = n;
while (g_systickCounter != 0U){
    }
    }


int main(void) {

        BOARD_InitBootPins();
        BOARD_InitBootClocks();
        BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
        BOARD_InitDebugConsole();

#endif





if (SysTick_Config(SystemCoreClock / 1500U)){

     }

while(1)       { */




















/*
            	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP, &ADC0_channelsConfig[0]);

    	        SysTick_DelayTicks(2000U);
    	        i++ ;

    	        while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP))) {
    	          }


                Vout= (ADC16_GetChannelConversionValue(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP) * (3.3 / 4096));
		        LUX =  (2 * ( 3.3 -( 3.3 / ADC16_GetChannelConversionValue(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP) )))*100;
                Iout= ((Vout)/10000);

            	PRINTF("ADC---> %d\r\n", ADC16_GetChannelConversionValue(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP));
               	PRINTF("LUX---> %.3f\r\n", LUX);
               	PRINTF("Vout---> %.3f\r\n", Vout);
               	PRINTF("Iout---> %f\r\n\n", Iout);


    	        __asm volatile ("nop");


    	        SysTick_DelayTicks(1000U);

    	        GPIO_PortToggle(BOARD_LED_GPIO_1,1u << BOARD_LED_GPIO_PIN_1);
    	        SysTick_DelayTicks(1000U);


    	        GPIO_PortToggle(BOARD_LED_GPIO_2, 1u << BOARD_LED_GPIO_PIN_2);
    	        SysTick_DelayTicks(1000);

    	        }

    return 0 ;
}  */
