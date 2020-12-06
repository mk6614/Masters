/*====================================================================
* Project:  Board Support Package (BSP)
* Function: Transmit and receive characters via TriCore's serial line
*           (Infineon controller TC26xx)
*           (polling variant)
*
* Copyright HighTec EDV-Systeme GmbH 1982-2019
*====================================================================*/
#define MODULE_UART_POLL
#define TCPATH tc26xb

#if (defined(__GNUC__))
#define TC_STR(s)		# s
	#define TC_INCLUDE(f)	TC_STR(f)
	#include TC_INCLUDE(TCPATH/Ifx_reg.h) // includes IfxCpu_reg.h, IfxCpu_bf.h and all others)
	#include TC_INCLUDE(TCPATH/IfxAsclin_bf.h)
	#include TC_INCLUDE(TCPATH/IfxAsclin_regdef.h)
 	#include "stdarg.h"
	#include "stdio.h"
	#include <string.h>

#elif (defined(__TASKING__))
	#ifdef __CPU__
	#include __SFRFILE__(__CPU__)
	#endif
#endif /* __GNUC__ || __TASKING__ */


static Ifx_ASCLIN* const asclin = (Ifx_ASCLIN *)&MODULE_ASCLIN0;
static Ifx_P * const port = (Ifx_P *)&MODULE_P15;

#define BUFSIZE	300

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

/* UART primitives */
#define TX_START(u)				((u)->FLAGSSET.U   = (IFX_ASCLIN_FLAGSSET_TFLS_MSK << IFX_ASCLIN_FLAGSSET_TFLS_OFF))
#define TX_READY(u)				((u)->FLAGS.B.TFL != 0)				/* Transmit FIFO Level */
#define RX_READY(u)				((u)->FLAGS.B.RFL != 0)				/* Receive FIFO Level */




/* Send character CHR via the serial line */
void _out_uart(const unsigned char chr)
{
	/* wait until space is available in the FIFO */
	while (!TX_READY(asclin))
		;

	TX_CLEAR(asclin);

	/* send the character */
	PUT_CHAR(asclin, chr);
}


/* Initialise asynchronous interface to operate at baudrate,8,n,1 */
void _init_uart(int baudrate)
{
	unsigned int numerator;
	unsigned int denominator;

	/* on board wiggler is connected to ASCLIN0 */
	/* ARX0B/P15.3 (RXD), ATX0/P15.2 (TXD) */
	/* Set TXD/P15.2 to "output" and "high" */
	port->IOCR0.B.PC2 = OUT_PPALT2; //set as output
	port->OMR.B.PS2 = 1; //set as high
	/* baudrate values at 100 MHz */
	denominator = 3125;
	switch (baudrate)
	{
		case   9600 : numerator =   BAUD_9600; break;
		case  19200 : numerator =  BAUD_19200; break;
		default     :
		case  38400 : numerator =  BAUD_38400; break;
		case  57600 : numerator =  BAUD_57600; break;
		case 115200 : numerator = BAUD_115200; break;
	}
	/* Enable ASCn */
	uint16_t psw = osEE_tc_get_cpu_wdt_pw(0);
	osEE_tc_clear_cpu_endinit(0, psw);
	asclin->CLC.U = 0;
	/* TXD and RXD pins: automotive level, fast */
	port->PDR0.B.PD2 = 0;
	port->PDR0.B.PD3 = 0;
	osEE_tc_set_cpu_endinit(0,psw);
	/* read back for activating module */
	(void)asclin->CLC.U;

	/* select ARX0B/P15.3 as input pin */
	asclin->IOCR.B.ALTI = 1;

	/* Program ASC0 */
	asclin->CSR.U = 0;

	/* configure TX and RX FIFOs */
	asclin->TXFIFOCON.U = (1 << 6)	/* INW: (1 == 1 byte) */
						  | (1 << 1)	/* ENO */
						  | (1 << 0);	/* FLUSH */
	asclin->RXFIFOCON.U = (1 << 6)	/* OUTW: (1 == 1 byte) */
						  | (1 << 1)	/* ENI */
						  | (1 << 0);	/* FLUSH */

	asclin->BITCON.U = ( 9 << 0)		/* PRESCALER: 10 */
					   | (15 << 16)		/* OVERSAMPLING: 16 */
					   | ( 9 << 24)		/* SAMPLEPOINT: position 7,8,9 */
					   | (1u << 31);	/* SM: 3 samples per bit */

	/* data format: 8N1 */
	asclin->FRAMECON.U = (1 << 9)		/* STOP: 1 bit */
						 | (0 << 16)	/* MODE: Init */
						 | (0 << 30);	/* PEN: no parity */
	asclin->DATCON.U = (7 << 0);		/* DATLEN: 8 bit */

	/* set baudrate value */
	asclin->BRG.U = (denominator << 0)	/* DENOMINATOR */
					| (numerator << 16);	/* NUMERATOR */

	asclin->FRAMECON.B.MODE = 1;		/* ASC mode */
	asclin->CSR.U = 1;				/* select CLC as clock source */

	TX_START(asclin);
}





static void my_printf(const char *fmt, ...)
{
	char buffer[BUFSIZE];
	char *ptr;
	va_list ap;

	va_start(ap, fmt);
	int ret = vsprintf(buffer, fmt, ap);
	va_end(ap);
	int i = 0;
	for (i = 0; i<ret ; i++)
		_out_uart((const unsigned char) buffer[i]);
}
