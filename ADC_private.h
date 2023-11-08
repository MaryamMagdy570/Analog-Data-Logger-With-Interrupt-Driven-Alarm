#ifndef _ADC_PRIVATE_H_
#define _ADC_PRIVATE_H_

#define AREF      0
#define AVCC      1
#define INTERNAL  2

#define RIGHT_ADJUSTMENT  0

#define LEFT_ADJUSTMENT   1


/*****/
#define SINGLE_CONVERSION 	0
#define AUTOTRIGGERED 		1
/*****/

#define FREE_RUNNING_MODE   0
/*****/


#define 	DIVID_BY_128  128



/************************************************/

#define  ADC_PORT   DIO_u8PORTA

/***************pin configuration****************/

#define  MUX0   0
#define  MUX1   1
#define  MUX2   2
#define  MUX3   3
#define  MUX4   4
#define  ADLAR  5
#define  REFS0  6
#define  REFS1  7

#define  ADPS0  0
#define  ADPS1  1
#define  ADPS2  2
#define  ADIE   3
#define  ADIF   4
#define  ADATE  5
#define  ADSC   6
#define  ADEN   7


#define ADTS0   5
#define ADTS1   6
#define ADTS2   7

#endif


