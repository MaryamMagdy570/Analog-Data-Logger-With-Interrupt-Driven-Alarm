#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_


void ADC_voidInit(void);

void ADC_voidEnable();
void ADC_voidDisable();

void ADC_voidInterruptEnable();
void ADC_voidInterruptDisable();


void ADC_voidStartConversionSync(u8 Copy_u8Channel);
void ADC_voidStartConversionAsync(u8 Copy_u8Channel);


u16 ADC_u16ReadADC();
u16 ADC_u16ReadADCInMV();


void ADC_SetCallback( void (*ptr) (void) );

void __vector_16(void) __attribute__((signal,used,externally_visible));  //to avoid optimization
void __vector_16(void);

#endif
