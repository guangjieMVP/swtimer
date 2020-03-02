
#include "cmd.h"


void event1(void)
{
	printf("1000ms >> RT-Thread\r\n");
}
EVENT_EXPORT(event1,ONCE_TYPE,event1);

void event2(void)
{
	printf("2000ms >> uCos\r\n");
}
EVENT_EXPORT(event2,ONCE_TYPE,event2);

void event3(void)
{
	printf("500ms >> Linux\r\n");
}
EVENT_EXPORT(event3,ONCE_TYPE,event3);

