#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "ADC_register.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"


/*
#define BAUD_RATE_ASYNC_NORMAL(baud_rate) ((F_CPU / (16UL * (baud_rate))) - 1)
#define BAUD_RATE_ASYNC_DOUBLE(baud_rate) ((F_CPU / (8UL * (baud_rate))) - 1)
#define BAUD_RATE_SYNC_MASTER(baud_rate)  ((F_CPU / (2UL * (baud_rate))) - 1)
*/
void ADC_voidInit(void)
{

	//ADC_voidEnable();

  #if VOLTAGE_REFERENCE == AVREF
    CLR_BIT(ADMUX,REFS1);
    CLR_BIT(ADMUX,REFS0);
  #elif VOLTAGE_REFERENCE == AVCC
    CLR_BIT(ADMUX,REFS1);
    SET_BIT(ADMUX,REFS0);
  #elif VOLTAGE_REFERENCE == INTERNAL
    SET_BIT(ADMUX,REFS1);
    SET_BIT(ADMUX,REFS0);
  #endif

  #if ADJUSTMENT == LEFT_ADJUSTMENT
    SET_BIT(ADMUX,ADLAR);
  #elif ADJUSTMENT == RIGHT_ADJUSTMENT
    CLR_BIT(ADMUX,ADLAR);
  #endif


  #if ADC_PRESCALLER == DIVID_BY_128
    SET_BIT(ADCSRA,ADPS2);
    SET_BIT(ADCSRA,ADPS1);
    SET_BIT(ADCSRA,ADPS0);

  #endif

  #if ADC_MODE == SINGLE_CONVERSION
    CLR_BIT(ADCSRA,ADATE);
  #elif ADC_MODE == AUTOTRIGGERED
    SET_BIT(ADCSRA,ADATE);
	#if ADC_AUTO_TRIGGER_SOURCE == FREE_RUNNING_MODE
		CLR_BIT(SFIOR,ADTS0);
		CLR_BIT(SFIOR,ADTS1);
		CLR_BIT(SFIOR,ADTS2);
    #endif
  #endif

} 


void ADC_voidEnable()
{
  SET_BIT(ADCSRA,ADEN);
}

void ADC_voidDisable()
{
  CLR_BIT(ADCSRA,ADEN);
}

void ADC_voidStartConversionSync(u8 Copy_u8Channel)
{
	//clearing channel
	ADMUX&=0b11100000;

	//setting the channel selected
	ADMUX|=Copy_u8Channel;

	//start conversion
	SET_BIT(ADCSRA,ADSC);

	while(!GET_BIT(ADCSRA,ADIF))
	{
		//POLLING : BUSY WAITING UNTIL EVENT
		//fix me: need time out
	}

	//CLEAR THE FLAG
	SET_BIT(ADCSRA,ADIF);
}


void ADC_voidStartConversionAsync(u8 Copy_u8Channel)
{
	ADMUX&=0b11100000;
	ADMUX|=Copy_u8Channel;
	SET_BIT(ADCSRA,ADSC);

}

u16 ADC_u16ReadADC()
{
	u16 Local_u16ADCRead;
	Local_u16ADCRead= ADC;

	return Local_u16ADCRead;

}

u16 ADC_u16ReadADCInMV()
{
	u16 Local_u16Analog;
	Local_u16Analog = (ADC * ADC_VREF* 1000ul) /1024;/// 256;//POWER(2,ADC_RESOLUTION);
	return Local_u16Analog;
}

void ADC_voidInterruptEnable()
{
	SET_BIT(ADCSRA,ADIE);
}

void ADC_voidInterruptDisable()
{
	CLR_BIT(ADCSRA,ADIE);
}


static void (*ADC_ptr) (void) = NULL;

void ADC_SetCallback( void (*ptr) (void) )
{
	if(ptr != NULL)
	{
		ADC_ptr = ptr;
	}

}



void __vector_16(void) __attribute__((signal,used,externally_visible));  //to avoid optimization
void __vector_16(void)
{
	if(ADC_ptr!= NULL)
		ADC_ptr();
}








