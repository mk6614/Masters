#ifndef TASK_DEFINITION_H_
#define TASK_DEFINITION_H_

#ifdef ERIKA_OS
    //#include "../ee.h"
#else
    #define TASK(name)  void name(void);\
                        void name(void)    
    #define CALL_TASK(name) name()
#endif


#ifdef  UNITTEST_ENV
    #warning compiling with unit test environment
#else
    #ifndef __GNUC__
        #error Compiler not known; define UNITTEST_ENV for unix like environment or __GNUC__ for HighTec GNUC compiler
    #endif
#endif

#endif //TASK_DEFINITION_H_
