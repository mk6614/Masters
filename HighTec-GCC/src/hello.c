/*====================================================================
* Project:  Board Support Package (BSP) examples
* Function: example using a serial line (polling mode)
*
* Copyright HighTec EDV-Systeme GmbH 1982-2019
*====================================================================*/


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "led.h"
#include "uart_poll.h"
#include "perf.h"

#ifdef __TRICORE__
#if defined(__TC161__)
#include "system_tc2x.h"
#endif /* __TC161__ */
#if defined(__TC162__)
#include "system_tc3x.h"
#endif /* __TC162__ */
#endif /* __TRICORE__ */

#ifdef MINIMAL_CODE
#include "usr_sprintf.h"
#define SPRINTF		usr_sprintf
#define VSPRINTF	usr_vsprintf
#else
#define SPRINTF		sprintf
#define VSPRINTF	vsprintf
#endif /* MINIMAL_CODE */

#define BUFSIZE		128

#ifndef BAUDRATE
#define BAUDRATE	38400
#endif /* BAUDRATE */


static void my_puts(const char *str)
{
	char buffer[BUFSIZE];
	char *ptr;

	SPRINTF(buffer, "%s\r\n", str);

	for (ptr = buffer; *ptr; ++ptr)
		_out_uart((const unsigned char) *ptr);
}

static void my_printf(const char *fmt, ...)
{
	char buffer[BUFSIZE];
	char *ptr;
	va_list ap;

	va_start(ap, fmt);
	VSPRINTF(buffer, fmt, ap);
	va_end(ap);

	for (ptr = buffer; *ptr; ++ptr)
		_out_uart((const unsigned char) *ptr);
}


int main(void)
{

#ifdef __TRICORE__
#if defined(__TC161__) || defined(__TC162__)
	SYSTEM_Init();
#endif /* __TC161__ || __TC162__ */
#endif /* __TRICORE__ */

	_init_uart(BAUDRATE);
	InitLED();
	my_printf("cpu clock: %lu\n", SYSTEM_GetCpuClock());
	performBasicTest(my_printf);


	return EXIT_SUCCESS;
}
