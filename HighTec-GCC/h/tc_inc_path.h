/*====================================================================
* Project:  Board Support Package (BSP)
* Function: macros for handling different AURIX TC26x devices and boards
*
* Copyright HighTec EDV-Systeme GmbH 1982-2019
*====================================================================*/

#ifndef __TC_INC_PATH_H__
#define __TC_INC_PATH_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__TC26XX__)
# if defined(TRIBOARD_TC26XX)
#  define TCPATH	tc26xx
# elif defined(TRIBOARD_TC26XA) || defined(APPKIT_TC265A)
#  define TCPATH	tc26xa
# elif defined(TRIBOARD_TC26XB) || defined(APPKIT_TC265B) || defined(APPKIT_TC267TFT)
#  define TCPATH	tc26xb
# else
#  error "Unknown TC26x board"
# endif /* TRIBOARD_TC26XX */
#else
# error "Unsupported AURIX device"
#endif /* __TC26XX__ */

#define TC_STR(s)		# s
#define TC_INCLUDE(f)	TC_STR(f)

/* check for application kits */
#if defined(APPKIT_TC265B) || defined(APPKIT_TC265A)
# define APPKIT_TC2X5	1
#else
# define APPKIT_TC2X5	0
#endif /* APPKIT_TC2X5 */
#if defined(APPKIT_TC267TFT)
# define APPKIT_TC2X7	1
#else
# define APPKIT_TC2X7	0
#endif /* APPKIT_TC2X7 */
#if (APPKIT_TC2X7 > 0) || (APPKIT_TC2X5 > 0)
# define RUN_ON_APPKIT	1
#else
# define RUN_ON_APPKIT	0
#endif /* APPKIT_TC2XX */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TC_INC_PATH_H__ */
