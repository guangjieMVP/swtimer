
/***********************************************************************
 * @file:     xxx.c
 * @author:   AresXu
 * @version:  v1.0.0
 * @date:    2019-11-xx
 * @brief: 
*************************************************************************/
#ifndef _SOFTWARE_TIMER_H_
#define _SOFTWARE_TIMER_H_


typedef struct __software_timer{
    unsigned int timeout;                                     //初始化时间计数器              
    unsigned int repeat;                                      //运行间隔：repeat > 0 :周期定时时间  repeat == 0 ：只定时一次
    void (*timeout_callback_handler)(void *para);    //超时回调函数
    struct __software_timer *next;
}swtimer_t;
   
void swtimer_init(swtimer_t *timer_handle,unsigned int timeout,unsigned int repeat,void (*timerout_cb)(void *));
void swtimer_start(swtimer_t *timer_handle);
void swtimer_stop(swtimer_t *timer_handle);
void swtimer_handle_loop(void);
void swtimer_ticks(void);

#endif