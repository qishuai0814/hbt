#ifndef __HBT_COMMON_H
#define __HBT_COMMON_H


#include "main.h"

void log_printf(const char *fmt, ...);


#define LOG(...)  do{\
    printf("[%s][%s][%d]", __FILE__, __FUNCTION__,__LINE__);\
    log_printf(__VA_ARGS__);\
    printf("\r\n");\
} while (0);


void read_line(char* str,FILE *in);



#endif
