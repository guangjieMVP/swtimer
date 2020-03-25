
#include "software_timer.h"
#include "string.h"

static swtimer_t swtimer_list_head = {0,0,(void *)0,(void *)0};

// static u32 timer_ticks_cnt = 0;

/**
  * @brief:         Determine if the software timer list is empty
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ      
  * @version:       v1.0.0
*/
static char is_swtimer_list_empty(void)
{
	if(swtimer_list_head.next == NULL)
		return 1;
	else
		return 0;
}

/**
  * @brief:         Insert the software timer node into the linked list
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ      
  * @version:       v1.0.0
*/
static void insert_swtimer(swtimer_t *timer_handle)
{
    swtimer_t *tmp;
	swtimer_t *prev;
    swtimer_t *list_head = &swtimer_list_head;

    if(is_swtimer_list_empty())
    {
        list_head->next = timer_handle;
    }
    else
    {
        tmp = list_head->next;
//        if(tmp == timer_handle)
//        {
//            return;
//        }
        while(tmp)
        {
			if(timer_handle == tmp)    //定时器已经存在
			{
				printf("The timer already exists\r\n");
				return;
			}
			prev = tmp;
            tmp = tmp->next; 
        }
        prev->next = timer_handle;
    }
}

/**
  * @brief:         Removes the software timer node from the list
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ       
  * @version:       v1.0.0
*/
static void remove_swtimer(swtimer_t *timer_handle)
{
    swtimer_t *list_head = &swtimer_list_head;
    swtimer_t *tmp = list_head;
	
	if(is_swtimer_list_empty())
		return;
	
    while(tmp && tmp->next != timer_handle)
    {
        tmp = tmp->next;
    }
	
	if(tmp == NULL)
		return;
	
	tmp->next          = timer_handle->next;
	timer_handle->next = NULL;	
}

/**
  * @brief:         Traverse the software timer list
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ             
  * @version:       v1.0.0
*/
void traverse_list(void)
{
	swtimer_t *tmp = &swtimer_list_head;
	tmp = tmp->next;
	while(tmp)
	{
		tmp->timeout_callback_handler((void *)0);
		tmp = tmp->next;
	}
}

/**
  * @brief:         Initializes the software timer
  * @param[in]:     timer_handle：Timer structure
  * @param[in]:     timeout ：Timer counter
  * @param[in]:     repeat :  = 0 single time ; > 0 , 
  * @param[in]:
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ             
  * @version:       v1.0.0
*/
void swtimer_init(swtimer_t *timer_handle,unsigned int timeout,unsigned int repeat,void (*timerout_cb)(void *))
{
	timer_handle->timeout                  = timeout;
	timer_handle->repeat                   = repeat;
	timer_handle->timeout_callback_handler = timerout_cb;
	timer_handle->next                     = (void *)0;
}

/**
  * @brief:         Start timer
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ       
  * @version:       v1.0.0
*/
void swtimer_start(swtimer_t *timer_handle)
{
	insert_swtimer(timer_handle);         
}

/**
  * @brief:         stop timer
  * @param[in]:     None
  * @retval[out]:   None
  * @note:            
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ      
  * @version:       v1.0.0
*/
void swtimer_stop(swtimer_t *timer_handle)
{
	remove_swtimer(timer_handle);        
}


/**
  * @brief:         Timer processing function
  * @param[in]:     None
  * @retval[out]:   None
  * @note:          Must be called by the main function  
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ       
  * @version:       v1.0.0
*/
void swtimer_handle_loop(void)
{
    swtimer_t *tmp = &swtimer_list_head;
	tmp = tmp->next;
	
    while(tmp)
    {
		if(tmp->timeout <= 0)
		{
            tmp->timeout_callback_handler((void *)0);

			if(tmp->repeat > 0)
			{
				tmp->timeout = tmp->repeat;
			}
			else     
			{
				swtimer_stop(tmp);
			}
		}
		tmp = tmp->next;
    } 
}

/**
  * @brief:         Provide a heartbeat to the software timer
  * @param[in]:     void
  * @retval[out]:   void
  * @note:          Must be called by 1ms hardware timer  
  * @author:        AresXu
  * @github:        https://github.com/EmbeddedXGJ      
  * @version:       v1.0.0
*/
void swtimer_ticks(void)
{
    swtimer_t *tmp = &swtimer_list_head;
	tmp = tmp->next;
	
	while(tmp)
	{
		if(tmp->timeout > 0)
		{
			tmp->timeout--;
		}
		tmp = tmp->next;
	}
}


