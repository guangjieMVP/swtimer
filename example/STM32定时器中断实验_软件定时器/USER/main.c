#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "software_timer.h"
#include "cmd.h"

void SoftWareTimer_Init(void);

int main(void)
{		
 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	event_init();
	SoftWareTimer_Init();
	TIM3_Int_Init(9,7199);   //10Khz的计数频率，计数到5000为500ms     1ms
	 
   	while(1)
	{
		software_timer_main_loop();
		event_handle_loop();
	}
}	 
 
