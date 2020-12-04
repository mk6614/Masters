/*
 * leds.h
 *
 *  Created on: 28 Oct 2020
 *      Author: Mojca Kolšek
 */

#ifndef LEDS_H_
#define LEDS_H_
#define TCPATH tc26xb

#if (defined(__GNUC__))
#define TC_STR(s)		# s
	#define TC_INCLUDE(f)	TC_STR(f)
	#include TC_INCLUDE(TCPATH/Ifx_reg.h) // includes IfxCpu_reg.h, IfxCpu_bf.h and all others)
	#include TC_INCLUDE(TCPATH/IfxPort_bf.h)
	#include TC_INCLUDE(TCPATH/IfxPort_regdef.h)
#elif (defined(__TASKING__))
	#ifdef __CPU__
	#include __SFRFILE__(__CPU__)
	#endif
#endif /* __GNUC__ || __TASKING__ */

static Ifx_P * const portLED = (Ifx_P *)&MODULE_P13;


#define MAX_LED					8	/* number of available LEDs */
#define LED_PIN_NR				6	/* pin number of first used LED */

#define MASK_ALL_LEDS			((1 << MAX_LED) - 1)

static void TURNOFFALL(void)
{
	P33_OUT.B.P13 = (uint8_t)1;
	P33_OUT.B.P12 = (uint8_t)1;
	P33_OUT.B.P11 = (uint8_t)1;
	P33_OUT.B.P10 = (uint8_t)1;
	P33_OUT.B.P9 = (uint8_t)1;
	P33_OUT.B.P8 = (uint8_t)1;
	P33_OUT.B.P7 = (uint8_t)1;
	P33_OUT.B.P6 = (uint8_t)1;
}

static __inline void initLEDs(void)
{
	P33_IOCR12.B.PC13  =   0x10;
	P33_IOCR12.B.PC12  =   0x10;
	P33_IOCR8.B.PC11   =   0x10;
	P33_IOCR8.B.PC10   =   0x10;
	P33_IOCR8.B.PC9    =   0x10;
	P33_IOCR8.B.PC8    =   0x10;
	P33_IOCR4.B.PC7    =   0x10;
	P33_IOCR4.B.PC6    =   0x10;
	TURNOFFALL();
}
static __inline void LEDON(unsigned int nr)
{
	switch (nr)
	{
		case 0:
			P33_OUT.B.P6 = 0;
			break;
		case 1:
			P33_OUT.B.P7 = 0;
			break;
		case 2:
			P33_OUT.B.P8 = 0;
			break;
		case 3:
			P33_OUT.B.P9 = 0;
			break;
		case 4:
			P33_OUT.B.P10 = 0;
			break;
		case 5:
			P33_OUT.B.P11 = 0;
			break;
		case 6:
			P33_OUT.B.P12 = 0;
			break;
		case 7:
			P33_OUT.B.P13 = 0;
			break;
		default:
			P33_OUT.B.P6 = 0;
			P33_OUT.B.P7 = 0;
			P33_OUT.B.P8 = 0;
			P33_OUT.B.P9 = 0;
			P33_OUT.B.P10 = 0;
			P33_OUT.B.P11 = 0;
			P33_OUT.B.P12 = 0;
			P33_OUT.B.P13 = 0;
			break;
	}
}

static __inline void LEDOFF(unsigned int nr)
{
	switch (nr)
	{
		case 0:
			P33_OUT.B.P6 = 1;
			break;
		case 1:
			P33_OUT.B.P7 = 1;
			break;
		case 2:
			P33_OUT.B.P8 = 1;
			break;
		case 3:
			P33_OUT.B.P9 = 1;
			break;
		case 4:
			P33_OUT.B.P10 = 1;
			break;
		case 5:
			P33_OUT.B.P11 = 1;
			break;
		case 6:
			P33_OUT.B.P12 = 1;
			break;
		case 7:
			P33_OUT.B.P13 = 1;
			break;
		default:
			P33_OUT.B.P6 = 1;
			P33_OUT.B.P7 = 1;
			P33_OUT.B.P8 = 1;
			P33_OUT.B.P9 = 1;
			P33_OUT.B.P10 = 1;
			P33_OUT.B.P11 = 1;
			P33_OUT.B.P12 = 1;
			P33_OUT.B.P13 = 1;
			break;
	}
}



#endif /* LEDS_H_ */
