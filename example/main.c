/************************************************************************
  * @file:     xxx.c
  * @author:   guangjieMVP
  * @github:   https://github.com/guangjieMVP
  * @version:  v1.0.0
  * @date:     2020-xx-xx
  * @brief:               
**************************************************************************/

#include "timer.h"
#include "software_timer.h"


swtimer_t timer1_t;
swtimer_t timer2_t;
swtimer_t timer3_t;

void timer1_cb(void *parm)
{
//	PRINT_INFO("1000ms >> dyy");
	post_event("uCosIII <->\r\n");
}

void timer2_cb(void *parm)
{
//	PRINT_INFO("2000ms >> dyy");
	post_event("RT-Thread->\r\n");
}

void timer3_cb(void *parm)
{
	post_event("Linux >>\r\n");
//	PRINT_INFO("500ms  >> dyy");
} 


void SoftWareTimer_Init(void)
{
    swtimer_init(&timer1_t,1000,1000,timer1_cb);
    swtimer_init(&timer2_t,2000,2000,timer2_cb);
    swtimer_init(&timer3_t,500,500,timer3_cb);

	swtimer_start(&timer1_t);
	swtimer_start(&timer2_t);
	swtimer_start(&timer3_t);

}

int main(void)
{		
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	
	SoftWareTimer_Init();
	TIM3_Int_Init(9,7199);   //10Khz的计数频率，计数到5000为500ms     1ms
	 
   	while(1)
	{
		swtimer_handle_loop();
	}
}	 


void TIM3_IRQHandler(void)   //TIM3中断  1ms中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		timer_ticks();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
	}
}
 
