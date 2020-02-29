/***********************************************************************
 * @file:        xxx.c
 * @author:      AresXu
 * @version:    v1.00.00
 * @date:       2019-11-xx
 * @brief: 
***********************************************************************/

#ifndef _EVENT_H_
#define _EVENT_H_


#if defined(__CC_ARM) || defined(__CLANG_ARM)   /* ARM Compiler */
    #define EVENT_SECTION(x)                  __attribute__((section(x)))
    #define EVENT_USED                    __attribute__((used))
#elif defined (__IAR_SYSTEMS_ICC__)             /* IAR Compiler */
    #define SECTION(x)                  @ x
    #define CMD_USED                    __root
#else
    #error "not supported tool chain..."
#endif

#define EVENT_OFF       0
#define EVENT_ON        1

typedef void (*event_handler)(void);

typedef struct _event {
    const char *event_name;
    char event_flag;
    event_handler    handler;
} event_t;

#define REGISTER_EVENT(event_name, handler)                                   \
    EVENT_USED event_t _register_##event_name EVENT_SECTION("EVENT_LIST")=    \
    {                                                                         \
        #event_name,                                                           \
        EVENT_OFF,                                                            \
        (event_handler)&handler                                               \
    };

void cmd_init(void);
void cmd_parsing(char *str);

#endif

