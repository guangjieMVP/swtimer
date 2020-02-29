
#include "cmd.h"


void event1(void)
{
	printf(">> guangjieSuper\r\n");
}
REGISTER_EVENT(event1,event1);

void event2(void)
{
	printf(">> solawc\r\n");
}
REGISTER_EVENT(event2,event2);

void event3(void)
{
	printf(">> pzibang\r\n");
}
REGISTER_EVENT(event3,event3);

