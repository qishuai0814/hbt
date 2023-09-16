#include "common.h"



void read_line(char* str,FILE *in)
{
    char *result;

    result = fgets(str,MAX_LINE_SIZE,in);
    if ((result == NULL) && !feof (in)) fprintf(stderr,"Error occurred while reading from file\n");
}


void log_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args,fmt);//解析：根据参数 fmt 的地址，获取 fmt 后面参数的地址，并保存在 args 指针变量中。
    vprintf(fmt,args);//打印：解析后的变参列表，直接传递给 vprintf 函数，实现打印功能。
    va_end(args);//释放：释放 args 指针，
}



