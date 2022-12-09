/******************************************************************************
 *
 * File Name: mini_pro4.c
 *
 * Description: mini-project 4 main file ultra-sonic project
 *
 * Date Creation: 16/10/2021
 *
 * Author: Youssef Abdel Aziz
 *
 *******************************************************************************/


#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */


void main(void)
{
	uint16 g_distance=0;/*a global variable to save the ultra-sonic sensor returned value */
	SREG |= (1<<7);/* Enable Global Interrupt I-Bit */
	Ultrasonic_init();/*initializing the ultra-sonic sensor driver*/
	LCD_init();/*initializing the LCD driver*/
	/*printing the main lines before the super loop*/
	LCD_displayString("Distance =    cm");
	LCD_moveCursor(2,3);
	LCD_displayString("ULTRA-SONIC");
	LCD_moveCursor(3,4);
	LCD_displayString("PROJECT 4");

	while(1)
	{
		Ultrasonic_Trigger();/*send the trigger pulse */
		g_distance=Ultrasonic_readDistance();/*storing measured distance in our global variable*/
		/*this if condition is to maintain the syntax of the LCD display */
		if(g_distance>=100)
		{
			LCD_moveCursor(0,11);/*start editing from the 11th place in the first line*/
			LCD_intgerToString(g_distance);/*displaying the measured distance on screen*/
		}

		else if(g_distance<100)
		{
			LCD_moveCursor(0,11);/*start editing from the 11th place in the first line*/
			LCD_intgerToString(g_distance);/*displaying the measured distance on screen*/
			LCD_displayString(" ");/*eliminating the extra number left from the old measurement*/
		}
	}
}
