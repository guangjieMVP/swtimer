/***********************************************************************
 * @file:        xxx.c
 * @author:      AresXu
 * @version:     v1.00.00
 * @date:        2019-11-xx
 * @brief: 
***********************************************************************/

#ifndef _EVENT_H_
#define _EVENT_H_


#if defined(__CC_ARM) || defined(__CLANG_ARM)   /* ARM Compiler */
    #define EVENT_SECTION(x)               __attribute__((section(x)))
    #define EVENT_USED                     __attribute__((used))
#elif defined (__IAR_SYSTEMS_ICC__)             /* IAR Compiler */
    #define SECTION(x)                  @ x
    #define CMD_USED                    __root
#else
    #error "not supported tool chain..."
#endif

#define EVENT_OFF       0
#define EVENT_ON        1

typedef enum _event_type{
	CONTINUOUS_TYPE = 0,
	ONCE_TYPE
}event_type_t;

typedef void (*event_handler)(void);

typedef struct _event {
    char event_flag : 1;
	event_type_t  event_type;
	const char    *event_name;
    event_handler    handler;
} event_t;

#define EVENT_EXPORT(event_name,event_type,handler)             \
	EVENT_USED event_t _##event_name##_event EVENT_SECTION("EVENT_LIST") = \
	{                                                                    \
		EVENT_OFF,                                                       \
		event_type,                                                      \
		#event_name,                                                     \
		(event_handler)&handler                                          \
	};

void event_init(void);
void open_event(char *event_name);
void close_event(char *event_name);
void event_handle_loop(void);
void set_eventtype_as_continuous(char *event_name);
void set_eventtype_as_once(char *event_name);
	
#endif

