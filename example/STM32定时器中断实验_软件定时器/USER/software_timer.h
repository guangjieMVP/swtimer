/**
  * @file:     xxx.c
  * @author:   AresXu
  * @version:  v1.0.0
  * @date:     2020-01-xx
  * @brief: 
*/

/***********************************************************************
 * @file:     xxx.c
 * @author:   AresXu
 * @version:  v1.0.0
 * @date:    2019-11-xx
 * @brief: 
*************************************************************************/
#ifndef _SOFTWARE_TIMER_H_
#define _SOFTWARE_TIMER_H_

#ifndef u32
#define u32 unsigned int
#endif

#ifndef u8 
#define u8 unsigned char 
#endif


typedef enum{
    FALSE = 0,
    TRUE = !FALSE,
}bool,BOOL;

typedef struct __software_timer{
    u32 timeout;                                     //初始化时间计数器              
    u32 repeat;                                      //运行间隔：repeat > 0 :周期定时时间  repeat == 0 ：只定时一次
    void (*timeout_callback_handler)(void *para);    //超时回调函数
    struct __software_timer *next;
}software_timer_t;
   
void software_timer_init(software_timer_t *timer_handle,u32 timeout,u32 repeat,void (*timerout_cb)(void *));
void software_timer_start(software_timer_t *timer_handle);
void software_timer_stop(software_timer_t *timer_handle);
void software_timer_main_loop(void);
void software_timer_ticks(void);

#endif