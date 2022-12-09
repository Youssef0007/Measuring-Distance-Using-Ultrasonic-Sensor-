/******************************************************************************
 *Module: ultra-sonic sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: ultra-sonic driver source file
 *
 * Date Creation: 16/10/2021
 *
 * Author: Youssef Abdel Aziz
 *
 *******************************************************************************/


#include "icu.h"
#include "gpio.h"
#include "common_macros.h"
#include "ultrasonic.h"
#include <util/delay.h> /* For the delay functions */
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
Icu_ConfigType g_ULTRASONC_configuration= {F_CPU_8,RISING};/*selecting the suitable configuration for ICU */

 uint8  g_ULTRASONIC_edgeCount = 0;
 uint16 g_ULTRASONIC_timeHigh = 0;
 float32 g_ULTRASONIC_total_distance=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
 /*
  * Description: This is the call back function called by the ICU driver.
 * This is used to calculate the high time (pulse time) generated by
 * the ultra-sonic sensor.*/

 void Ultrasonic_edgeProcessing(void)
 {
 	g_ULTRASONIC_edgeCount++;
 	if(g_ULTRASONIC_edgeCount == 1)
 	{
 		/*Clear the timer counter register to start measurements from the
 		 * first detected rising edge
 		 */
 		Icu_clearTimerValue();
 		/* Detect falling edge */
 		Icu_setEdgeDetectionType(FALLING);
 	}
 	else if(g_ULTRASONIC_edgeCount == 2)
 	{
 		/* Store the High time value */
 		g_ULTRASONIC_timeHigh = Icu_getInputCaptureValue();
 		/* Detect rising edge */
 		Icu_setEdgeDetectionType(RISING);
 		g_ULTRASONIC_edgeCount=0;
 	}
 }

 /*
 * Description:Initialize the ICU driver as required.
 *  Setup the ICU call back function.
 *  Setup the direction for the trigger pin as output pin through the
 *  GPIO driver
 */

void Ultrasonic_init(void)
{
	Icu_init(&g_ULTRASONC_configuration);/*ICU initialization*/
	Icu_setCallBack(Ultrasonic_edgeProcessing);/*set the call back function*/
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID , PIN_OUTPUT);/*trigger pin output*/
}
/*
 * Description:Send the Trigger pulse to the ultra-sonic.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID , LOGIC_HIGH);/*set the trigger pin*/
	_delay_ms(20);/*delay more than 10 micro-secs to allow the eight the pulses to generate from the ultra-sonic */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID , LOGIC_LOW);/*set the trigger pin*/
}
/*
 * Function Name :Ultrasonic_readDistance
 * Description:Send the trigger pulse by using Ultrasonic_Trigger function.
*  Start the measurements by the ICU from this moment.
*  Return: The measured distance in Centimeter*/
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();/*send trigger pulse*/
	g_ULTRASONIC_total_distance=g_ULTRASONIC_timeHigh/57.5;/*calculating the total distance*/
	return g_ULTRASONIC_total_distance;
}

