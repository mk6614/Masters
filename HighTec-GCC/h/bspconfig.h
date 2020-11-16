/*====================================================================
* Project:  Board Support Package (BSP)
* Function: BSP configuration header file.
*           (Infineon TC26xx boards)
*
* Copyright HighTec EDV-Systeme GmbH 1982-2019
*====================================================================*/

#ifndef __BSPCONFIG_H__
#define __BSPCONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <machine/intrinsics.h>

#include "tc_inc_path.h"

#include TC_INCLUDE(TCPATH/IfxCpu_reg.h)
#include TC_INCLUDE(TCPATH/IfxStm_reg.h)
#include TC_INCLUDE(TCPATH/IfxCpu_bf.h)

#if defined(TRIBOARD_TC26XA)
# define BOARD_NAME				"TriBoard-TC26xA"
# define BOARD_TITLE			"TC26xA TriBoard"
# define MCU_NAME				"TC26xA"
#elif defined(APPKIT_TC265A)
# define BOARD_NAME				"AppKit-TC265A"
# define BOARD_TITLE			"TC265A AppKit"
# define MCU_NAME				"TC265A"
#elif defined(TRIBOARD_TC26XB)
# define BOARD_NAME				"TriBoard-TC26xB"
# define BOARD_TITLE			"TC26xB TriBoard"
# define MCU_NAME				"TC26xB"
#elif defined(APPKIT_TC265B)
# define BOARD_NAME				"AppKit-TC265B"
# define BOARD_TITLE			"TC265B AppKit"
# define MCU_NAME				"TC265B"
#elif defined(APPKIT_TC267TFT)
# define BOARD_NAME				"AppKit-TC267TFT"
# define BOARD_TITLE			"TC267TFT AppKit"
# define MCU_NAME				"TC267B"
#endif /* TRIBOARD_TC26XA || APPKIT_TC265A */

#define CPU_CLOCK				200
#define TIM_CLOCK				(CPU_CLOCK)
#define	TICKS_PER_SEC			((CPU_CLOCK / 2) * 1000000)
#define TIMTICKS				_mfcr(CPU_CCNT)
#define TIM_SCALE				(CPU_CLOCK / TIM_CLOCK)
#define GET_CORE_ID()			(_mfcr(CPU_CORE_ID) & IFX_CPU_CORE_ID_CORE_ID_MSK)

#ifndef DEFAULT_PLL_VALUE
#define DEFAULT_PLL_VALUE		PLL_VALUE_200_100
#endif /* DEFAULT_PLL_VALUE */


#include TC_INCLUDE(TCPATH/IfxPort_reg.h)
#include TC_INCLUDE(TCPATH/IfxPort_bf.h)

#if (APPKIT_TC2X7 == 1)
static Ifx_P * const portLED = (Ifx_P *)&MODULE_P13;
#else
static Ifx_P * const portLED = (Ifx_P *)&MODULE_P33;
#endif /* APPKIT_TC2X7 */

#if (APPKIT_TC2X5 == 1)
/* AppKit-TC2X5: P33.8 .. P33.11 --> LED D107 ... D110 */

#define MAX_LED					4	/* number of available LEDs */
#define LED_PIN_NR				8	/* pin number of first used LED */
#elif defined(APPKIT_TC267TFT)
/* AppKit-TC2X7: P13.0 .. P13.3 --> LED D107 ... D110 */

#define MAX_LED					4	/* number of available LEDs */
#define LED_PIN_NR				0	/* pin number of first used LED */
#else
/* TriBoard-TC26xx: P33.6 ... P33.13 --> LED D501 ... D508 */

#define MAX_LED					8	/* number of available LEDs */
#define LED_PIN_NR				6	/* pin number of first used LED */
#endif /* APPKIT_TC2X5 */

#define MASK_ALL_LEDS			((1 << MAX_LED) - 1)

/* OMR is WO ==> don't use load-modify-store access! */
/* set PSx pin */
#define LED_PIN_SET(x)			(1 << (LED_PIN_NR + (x)))
/* set PCLx pin */
#define LED_PIN_RESET(x)		(1 << (LED_PIN_NR + IFX_P_OMR_PCL0_OFF + (x)))
#define LED_ON(x)				(portLED->OMR.U = LED_PIN_RESET(x))
#define LED_OFF(x)				(portLED->OMR.U = LED_PIN_SET(x))
/* set PCLx and PSx pin to 1 ==> toggle pin state */
#define LED_TOGGLE(x)			(portLED->OMR.U = LED_PIN_RESET(x) | LED_PIN_SET(x))

#if (APPKIT_TC2X5 == 1)
#define INIT_LEDS				{\
	/* initialise all LEDs (P33.8 .. P33.11) */\
	portLED->IOCR8.U = 0x80808080;	/* OUT_PPGPIO */\
	/* all LEDs OFF */\
	portLED->OMR.U = (MASK_ALL_LEDS << LED_PIN_NR);\
}
#elif (APPKIT_TC2X7 == 1)
#define INIT_LEDS				{\
	/* initialise all LEDs (P13.0 .. P13.3) */\
	portLED->IOCR0.U = 0x80808080;	/* OUT_PPGPIO */\
	/* all LEDs OFF */\
	portLED->OMR.U = (MASK_ALL_LEDS << LED_PIN_NR);\
}
#else
#define INIT_LEDS				{\
	/* initialise all LEDs (P33.6 .. P33.13) */\
	portLED->IOCR4.B.PC6 = 0x10;	/* OUT_PPGPIO */\
	portLED->IOCR4.B.PC7 = 0x10;	/* OUT_PPGPIO */\
	portLED->IOCR8.U = 0x80808080;	/* OUT_PPGPIO */\
	portLED->IOCR12.B.PC12 = 0x10;	/* OUT_PPGPIO */\
	portLED->IOCR12.B.PC13 = 0x10;	/* OUT_PPGPIO */\
	/* all LEDs OFF */\
	portLED->OMR.U = (MASK_ALL_LEDS << LED_PIN_NR);\
}
#endif /* APPKIT_TC2X5 */


/*********************************************************/
/* Common UART settings (interrupt and polling variants) */
/*********************************************************/
#if (defined(MODULE_UART_INT) || defined(MODULE_UART_POLL))

#include TC_INCLUDE(TCPATH/IfxAsclin_reg.h)
#include TC_INCLUDE(TCPATH/IfxAsclin_bf.h)

static Ifx_ASCLIN * const asclin0 = (Ifx_ASCLIN *)&MODULE_ASCLIN0;
#if (RUN_ON_APPKIT == 1)
static Ifx_P * const port = (Ifx_P *)&MODULE_P14;
#else
static Ifx_P * const port = (Ifx_P *)&MODULE_P15;
#endif /* RUN_ON_APPKIT */

#define UARTBASE				asclin0

/* baud rate values at 100 MHz */
#define BAUD_9600				(48 * 1)
#define BAUD_19200				(48 * 2)
#define BAUD_38400				(48 * 4)
#define BAUD_57600				(48 * 6)
#define BAUD_115200				(48 * 12)

/* Port Modes */
#define IN_NOPULL0				0x00	/* Port Input No Pull Device */
#define IN_PULLDOWN				0x01	/* Port Input Pull Down Device */
#define IN_PULLUP				0x02	/* Port Input Pull Up Device */
#define IN_NOPULL3				0x03	/* Port Input No Pull Device */
#define OUT_PPGPIO				0x10	/* Port Output General Purpose Push/Pull */
#define OUT_PPALT1				0x11	/* Port Output Alternate 1 Function Push/Pull */
#define OUT_PPALT2				0x12	/* Port Output Alternate 2 Function Push/Pull */
#define OUT_PPALT3				0x13	/* Port Output Alternate 3 Function Push/Pull */
#define OUT_PPALT4				0x14	/* Port Output Alternate 4 Function Push/Pull */
#define OUT_PPALT5				0x15	/* Port Output Alternate 5 Function Push/Pull */
#define OUT_PPALT6				0x16	/* Port Output Alternate 6 Function Push/Pull */
#define OUT_PPALT7				0x17	/* Port Output Alternate 7 Function Push/Pull */
#define OUT_ODGPIO				0x18	/* Port Output General Purpose Open Drain */
#define OUT_ODALT1				0x19	/* Port Output Alternate 1 Function Open Drain */
#define OUT_ODALT2				0x1A	/* Port Output Alternate 2 Function Open Drain */
#define OUT_ODALT3				0x1B	/* Port Output Alternate 3 Function Open Drain */
#define OUT_ODALT4				0x1C	/* Port Output Alternate 4 Function Open Drain */
#define OUT_ODALT5				0x1D	/* Port Output Alternate 5 Function Open Drain */
#define OUT_ODALT6				0x1E	/* Port Output Alternate 6 Function Open Drain */
#define OUT_ODALT7				0x1F	/* Port Output Alternate 7 Function Open Drain */

/* definitions for RX error conditions */
#define ASC_ERROR_MASK			((IFX_ASCLIN_FLAGS_PE_MSK << IFX_ASCLIN_FLAGS_PE_OFF) | \
								 (IFX_ASCLIN_FLAGS_FE_MSK << IFX_ASCLIN_FLAGS_FE_OFF) | \
								 (IFX_ASCLIN_FLAGS_RFO_MSK << IFX_ASCLIN_FLAGS_RFO_OFF))

#define ASC_CLRERR_MASK			((IFX_ASCLIN_FLAGSCLEAR_PEC_MSK << IFX_ASCLIN_FLAGSCLEAR_PEC_OFF) | \
								 (IFX_ASCLIN_FLAGSCLEAR_FEC_MSK << IFX_ASCLIN_FLAGSCLEAR_FEC_OFF) | \
								 (IFX_ASCLIN_FLAGSCLEAR_RFOC_MSK << IFX_ASCLIN_FLAGSCLEAR_RFOC_OFF))

/* UART primitives */
#define RX_CLEAR(u)				((u)->FLAGSCLEAR.U = (IFX_ASCLIN_FLAGSCLEAR_RFLC_MSK << IFX_ASCLIN_FLAGSCLEAR_RFLC_OFF))
#define TX_CLEAR(u)				((u)->FLAGSCLEAR.U = (IFX_ASCLIN_FLAGSCLEAR_TFLC_MSK << IFX_ASCLIN_FLAGSCLEAR_TFLC_OFF))
#define PUT_CHAR(u, c)			((u)->TXDATA.U = (c))
#define GET_CHAR(u)				((u)->RXDATA.U)
#define GET_ERROR_STATUS(u)		(((u)->FLAGS.U) & ASC_ERROR_MASK)
#define RESET_ERROR(u)			((u)->FLAGSCLEAR.U = ASC_CLRERR_MASK)

#endif /* (defined(MODULE_UART_INT) || defined(MODULE_UART_POLL)) */


/************************/
/* Polling variant UART */
/************************/
#ifdef MODULE_UART_POLL

/* UART primitives */
#define TX_START(u)				((u)->FLAGSSET.U   = (IFX_ASCLIN_FLAGSSET_TFLS_MSK << IFX_ASCLIN_FLAGSSET_TFLS_OFF))
#define TX_READY(u)				((u)->FLAGS.B.TFL != 0)				/* Transmit FIFO Level */
#define RX_READY(u)				((u)->FLAGS.B.RFL != 0)				/* Receive FIFO Level */

#endif /* MODULE_UART_POLL */


/**************************/
/* Interrupt variant UART */
/**************************/
#ifdef MODULE_UART_INT

#include "interrupts.h"

extern void _uart_init_bsp(int baudrate, void (*uart_rx_isr)(int arg), void (*uart_tx_isr)(int arg));

#define XMIT_INTERRUPT			3
#define RECV_INTERRUPT			4

/* UART primitives */
#define TX_INT_START(u)			((u)->FLAGSENABLE.B.TFLE = 1, (u)->FLAGSSET.U = (IFX_ASCLIN_FLAGSSET_TFLS_MSK << IFX_ASCLIN_FLAGSSET_TFLS_OFF))
#define TX_INT_STOP(u)			((u)->FLAGSENABLE.B.TFLE = 0)
#define TX_INT_CHECK(u)			((u)->FLAGSENABLE.B.TFLE)

#endif /* MODULE_UART_INT */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __BSPCONFIG_H__ */
