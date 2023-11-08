/*
 * main.c
 *
 *  Created on: Oct 31, 2023
 *      Author: Maryam Magdy
 */

/* Task: Analog Data Logger with Interrupt-Driven Alarms
 * Requirements: The system will continuously monitor an analog sensor (Lm35 ,LDR , any other sensor)
 * using the Analog-to-Digital Converter (ADC).
 * When the value exceeds level it triggers external interrupt
 * that Turns on the buzzer and display on LCD the sensor source
 * */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"


//callback prototypes
void EXTI0_ISR();
void EXTI1_ISR();
void EXTI2_ISR();

void ADC_CHAINING_ISR();


//global variables
volatile u8 Channels[3]={0,1,4};
volatile u16 Readings[3]={0,0,0};
volatile u8 ChannelIndex = 0;

int main (void)
{
	ADC_SetCallback(ADC_CHAINING_ISR);
	EXTI0_CallBack(EXTI0_ISR);
	EXTI1_CallBack(EXTI1_ISR);
    EXTI2_CallBack(EXTI2_ISR);


	DIO_voidInit();
	EXTI_voidInit();
	ADC_voidInit();
	CLCD_voidInit();

	GIE_voidEnable();

	ADC_voidEnable();
	ADC_voidInterruptEnable();

	EXTI0_voidEnable();
	EXTI1_voidEnable();
	EXTI2_voidEnable();


	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);

	CLCD_voidGoToRowColumn(0,0);
	CLCD_voidSendString("Sensor1: ");

	CLCD_voidGoToRowColumn(1,0);
	CLCD_voidSendString("Sensor2: ");

	CLCD_voidGoToRowColumn(2,0);
	CLCD_voidSendString("Sensor3: ");

	ADC_voidStartConversionAsync(Channels[ChannelIndex]);



	while(1)
	{
		GIE_voidDisable();
		CLCD_voidGoToRowColumn(0,9);
		CLCD_voidSendInteger(Readings[0]/10);
		CLCD_voidGoToRowColumn(1,9);
		CLCD_voidSendInteger(Readings[1]/10);
		CLCD_voidGoToRowColumn(2,9);
		CLCD_voidSendInteger(Readings[2]/10);
		GIE_voidEnable();
		switch(ChannelIndex)
		{
		case 0:
				if (Readings[0] > 400)
				{
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_HIGH);
				}
				else
				{
					CLCD_voidGoToRowColumn(0,15);
					CLCD_voidSendString("    ");
				}
				break;
		case 1:
				if (Readings[1] > 400)
				{
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_HIGH);
				}
				else
				{
					CLCD_voidGoToRowColumn(1,15);
					CLCD_voidSendString("    ");
				}
				break;
		case 2:
				if (Readings[2] > 400)
				{
					DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);
				}
				else
				{
					CLCD_voidGoToRowColumn(2,15);
					CLCD_voidSendString("    ");
				}
				break;
		}

		if (!(Readings[0] > 400 || Readings[1] > 400 ||Readings[2] > 400))
		{
			DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_LOW);  //RED LED
			DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN6,DIO_u8PIN_LOW);  //RED LED
		}

	}
	return 0;
}

void EXTI0_ISR()
{
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_HIGH);  //RED LED
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN6,DIO_u8PIN_HIGH);  //BUZZER
	CLCD_voidGoToRowColumn(0,15);
	CLCD_voidSendString("Fire");

	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_LOW);
}
void EXTI1_ISR()
{
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_HIGH);  //RED LED
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN6,DIO_u8PIN_HIGH);  //BUZZER
	CLCD_voidGoToRowColumn(1,15);
	CLCD_voidSendString("Fire");

	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_LOW);
}
void EXTI2_ISR()
{
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_HIGH);  //RED LED
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN6,DIO_u8PIN_HIGH);  //BUZZER
	CLCD_voidGoToRowColumn(2,15);
	CLCD_voidSendString("Fire");

	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
}


void ADC_CHAINING_ISR()
{

	ADC_voidDisable();
	Readings[ChannelIndex] = ADC_u16ReadADCInMV();
	ADC_voidEnable();
	ChannelIndex++;

	if (ChannelIndex == 3)
		ChannelIndex = 0;

	ADC_voidStartConversionAsync(Channels[ChannelIndex]);


}



