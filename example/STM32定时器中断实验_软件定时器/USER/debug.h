/***********************************************************************
 * @file:     xxx.c
 * @author:   AresXu
 * @version:  v1.0.0
 * @date:     2020-01-xx
 * @brief: 
*************************************************************************/
#ifndef _DEBUG_H_
#define _DEBUG_H_


#define DEBUG_PRINT_INFO_ENABLE
#define DEBUG_PRINT_ERR_ENABLE
#define PRINT_INFO_ENABLE        

#ifdef  DEBUG_PRINT_INFO_ENABLE
#define DEBUG_PRINT_INFO(fmt,arg...)    do{printf("<<-[DEBUG_INFO]->> "fmt"\n",##arg);}while(0)    
#else
#define DEBUG_PRINT_INFO(fmt,arg...)  
#endif

#ifdef  DEBUG_PRINT_ERR_ENABLE
#define DEBUG_PRINT_ERR(fmt,arg...)     do{printf("<<-[EER]->> "fmt"\n",##arg);}while(0)    
#else
#define DEBUG_PRINT_INFO(fmt,arg...)  
#endif

#ifdef  PRINT_INFO_ENABLE
#define PRINT_INFO(fmt,arg...)          do{printf("<<-[INFO]->> "fmt"\r\n",##arg);}while(0)    
#else
#define PRINT_INFO(fmt,arg...)  
#endif


#endif