
#include "event.h"
#include <stdio.h>
#include <string.h>

static event_t *_event_list_begin, *_event_list_end;

static event_t *_match_event(char *event_name)
{
	event_t *index;
	
	if(!event_name)
		return NULL;
	
	for(index = _event_list_begin; index < _event_list_end; index++)
    {
        if(strncmp(event_name,index->event_name,strlen(index->event_name)) == 0)
        {
			return index;
        }
    }
	return NULL;
}

void event_init(void)
{
	event_t *index;
#if defined(__CC_ARM) || defined(__CLANG_ARM)          /* ARM C Compiler */
    extern const int EVENT_LIST$$Base;
    extern const int EVENT_LIST$$Limit;
    _event_list_begin = (event_t *)&EVENT_LIST$$Base;
    _event_list_end   = (event_t *)&EVENT_LIST$$Limit;
#elif defined (__ICCARM__) || defined(__ICCRX__)      /* for IAR Compiler */
    _cmd_init(__section_begin("EVENT_LIST"), __section_end("EVENT_LIST"));
#endif
	for(index = _event_list_begin; index < _event_list_end; index++)
    {
		printf("%s\r\n",index->event_name);
	}
}

void open_event(char *event_name)
{
	if(!event_name)
		return;
	
    event_t *event = _match_event(event_name);
	
	if(event != NULL)
	{
		if(event->event_type == ONCE_TYPE)
			event->event_flag = EVENT_ON;
	}
}

void close_event(char *event_name)
{
	if(!event_name)
		return;
	
    event_t *event = _match_event(event_name);
	
	if(event != NULL)
	{
		event->event_flag = EVENT_OFF;
	}
}

void set_eventtype_as_continuous(char *event_name)
{
	if(!event_name)
		return;
	
    event_t *event = _match_event(event_name);
	
	if(event != NULL)
	{
		event->event_type = CONTINUOUS_TYPE;
	}
}

void set_eventtype_as_once(char *event_name)
{
	if(!event_name)
		return;
	
    event_t *event = _match_event(event_name);
	
	if(event != NULL)
	{
		event->event_type = ONCE_TYPE;
	}
}

void event_handle_loop(void)
{
    event_t *index;
    for(index = _event_list_begin; index < _event_list_end; index++)
    {
		if(index->event_type ==  CONTINUOUS_TYPE)
		{
			index->handler();
		}
        else if(index->event_type ==  ONCE_TYPE)
		{
			if(index->event_flag == EVENT_ON)
			{
				index->handler();
				index->event_flag = EVENT_OFF;
			}
		}
    }    
}

